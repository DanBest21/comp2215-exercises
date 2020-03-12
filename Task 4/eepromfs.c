/* COMP2215  Task 4---PART OF A MODEL ANSWER

   Klaus-Peter Zauner, 2014-2016

   NOTE: NO WEAR LEVELING IS PERFORMED BY THIS CODE:
         JUST FOR DEMONSTRATION---DO NOT USE IN PRODUCTION CODE
*/

#include "eepromfs.h"
#include "lcd.h"

/* Servers as magic cookie to recognize file system:  */
#define FSVERSION_UINT16  14301

#define TOTALBLOCKS  EEPROM_LEN/BLOCK_SIZE

typedef uint8_t block;
typedef uint8_t filename;

typedef struct entry 
{
    block  startblock;
    uint16_t length;
    uint16_t currpos;
} direntry;


typedef struct meta 
{
    uint16_t version;
    direntry dir[MAX_FILES];   /* 5 B * 10 = 50 B */
    block fat[TOTALBLOCKS];    /* (1600 B) / (64 B/block) = 25 blocks */
} metadata;

block getfreeblock(void);
void freeblockchain(block start);

metadata fsmeta;

void init_eepromfs() 
{
    filename fn;
    block    bl;

    init_lcd();

    printf( "Dir entry size: %u\n", sizeof(direntry) );
    printf( "Meta data size: %u\n", sizeof(metadata) );

    /* Load Meta data */
    eeprom_read_block((void *) &fsmeta,
                     (const void *) EEPROM_START, sizeof(metadata));

    /* Check whether file system exists */
    printf( "FS Version: %u\n", fsmeta.version );
    if (fsmeta.version !=  FSVERSION_UINT16) 
    {
	    /* Inititalise blank FS */
	    fsmeta.version = FSVERSION_UINT16;
	    for (fn=0; fn <  MAX_FILES; fn++ )
        {
		    fsmeta.dir[fn].startblock = FREE_BLOCK; /* Not a file */
		    fsmeta.dir[fn].length = 0;
		    fsmeta.dir[fn].currpos = CLOSED_FILE;
	    }

        for (bl=0; bl < TOTALBLOCKS; bl++) 
        {
	        fsmeta.fat[bl] = FREE_BLOCK;
	    }

        /* Write blank FS ("format") */
        eeprom_update_block((void *) &fsmeta,
                            (void *) EEPROM_START, sizeof(metadata));
    } 
    else 
    {
        /* List Files */
	    printf( "FS found: v%u\n", fsmeta.version );

	    for (fn=0; fn <  MAX_FILES; fn++ )
        {
		    fsmeta.dir[fn].currpos = CLOSED_FILE;

		    if (fsmeta.dir[fn].startblock != FREE_BLOCK)
            {
			    printf( "File %d  with length: %d\n",
			            fn, fsmeta.dir[fn].length );
		    }
	    }
    }

}

void open_for_write(filename fn) 
{
    block start;

    start = fsmeta.dir[fn].startblock;

    if (start != FREE_BLOCK) 
    {
	    if (fsmeta.dir[fn].currpos != CLOSED_FILE) 
        {
		    printf( "ERROR: File %d already open!\n", fn );
		    return;
	    }

	    /* Overwrite existing file */
	    printf( "Overwrite existing file %d... \n", fn );
	    freeblockchain( start );
    }

    fsmeta.dir[fn].length = 0;

    if ((fsmeta.dir[fn].startblock = getfreeblock()) == FREE_BLOCK) 
    {
	    printf( "ERROR: Out of EEPROM space.\n" );
	    return;
    } 
    else 
    {
	    fsmeta.dir[fn].currpos = 0;
    }
}

void open_for_append(filename fn)
{
    block start;
    
    start = fsmeta.dir[fn].startblock;

    if (start != FREE_BLOCK)
    {
        if (fsmeta.dir[fn].currpos != CLOSED_FILE) 
        {
		    printf( "ERROR: File %d already open!\n", fn );
		    return;
	    }

        printf( "Appending to existing file %d... \n", fn );
        fsmeta.dir[fn].currpos = fsmeta.dir[fn].length;
    }
    else
    {
        open_for_write(fn);
    }
}

void open_for_read(filename fn)
{
    block start;

    start = fsmeta.dir[fn].startblock;

    if (start != FREE_BLOCK)
    {
        if (fsmeta.dir[fn].currpos != CLOSED_FILE) 
        {
		    printf( "ERROR: File %d already open!\n", fn );
		    return;
	    }

        printf( "Opening file %d to be read... \n", fn);
        fsmeta.dir[fn].currpos = 0;
    }
    else
    {
        printf( "ERROR: File %d does not exist. \n ", fn);
    }
}

void close(filename fn) 
{
    if (fsmeta.dir[fn].startblock == FREE_BLOCK) 
    {
	    printf( "ERROR: File %d does not exist.\n", fn);
        return;
    }

    if (fsmeta.dir[fn].currpos == CLOSED_FILE) 
    {
        printf( "ERROR: File %d is not open.\n", fn);
        return;
    }

    fsmeta.dir[fn].currpos = CLOSED_FILE;
    eeprom_update_block((void *) &fsmeta,
			(void *) EEPROM_START, sizeof(metadata));

}

void delete(filename fn) 
{
    block start;

    start = fsmeta.dir[fn].startblock;

    if (start == FREE_BLOCK) 
    {
	    printf( "ERROR delete: File %d does not exist.\n", fn);
	    return;
    }

    fsmeta.dir[fn].startblock = FREE_BLOCK; /* Not a file */
    fsmeta.dir[fn].length = 0;
    fsmeta.dir[fn].currpos = CLOSED_FILE;

    freeblockchain(start);

    eeprom_update_block((void *) &fsmeta,
                        (void *) EEPROM_START, sizeof(metadata));
}

/* NOTE: We check only if it is open, but do not
         distinguish between open for reading and
         open for writing.
*/

void write(filename fn, uint8_t *buff, uint16_t len) 
{
    uint16_t loc;
    uint16_t idx;
    block currbl;

    if (fsmeta.dir[fn].currpos == CLOSED_FILE) 
    {
	    printf( "ERROR: File %d not open.\n", fn);
	    return;
    }

    for (loc=fsmeta.dir[fn].currpos, idx=0; idx < len; idx++, loc++) 
    {
	    // Write the value of the buffer to the appropriate place in the file system.
        currbl = (*buff + idx);
        fsmeta.fat[loc] = currbl;
    }

    eeprom_update_block((void *) &fsmeta,
                        (void *) EEPROM_START, sizeof(metadata));
}

void read(filename fn, uint8_t *buff, uint16_t len)
{
    uint16_t loc;
    uint16_t idx;
    block currbl;

    if (fsmeta.dir[fn].currpos == CLOSED_FILE) 
    {
	    printf( "ERROR: File %d not open.\n", fn);
	    return;
    }

    for (loc=fsmeta.dir[fn].currpos, idx=0; idx < len; idx++, loc++) 
    {
	    // Add the contents of the file to the passed buffer.
        currbl = fsmeta.fat[loc];
        (*buff + idx) = currbl;
    }
}

block getfreeblock(void)
{
    block bl;

    for (bl=0; bl < TOTALBLOCKS; bl++) 
    {
	    if ( fsmeta.fat[bl] == FREE_BLOCK )
        {
		    fsmeta.fat[bl] = END_BLOCK;
		    return bl;
	    }
    }
    /* Error: No space left */
    return FREE_BLOCK;
}

void freeblockchain(block start) 
{
    block next;

    if (start == FREE_BLOCK) 
    {
	    printf( "ERROR: Free block in chain? Start %d", start);
    }

    while ((next=fsmeta.fat[start]) != END_BLOCK) 
    {
	    fsmeta.fat[start] = FREE_BLOCK;
	    start = next;

	    if (start == FREE_BLOCK) 
        {
		    printf( "ERROR: Free block in chain? Start %d", start);
	    }
    }

    fsmeta.fat[start] = FREE_BLOCK;
}