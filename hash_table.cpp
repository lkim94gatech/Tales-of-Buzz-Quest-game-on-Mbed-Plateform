// ============================================
// The HashTable class file
//
// Copyright 2023 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================

/****************************************************************************
 * Include the Public Interface
 *
 * By including the public interface at the top of the file, the compiler can
 * enforce that the function declarations in the the header are not in
 * conflict with the definitions in the file. This is not a guarantee of
 * correctness, but it is better than nothing!
 ***************************************************************************/
#include "hash_table.h"

/****************************************************************************
 * Include other private dependencies
 *
 * These other modules are used in the implementation of the hash table module,
 * but are not required by users of the hash table.
 ***************************************************************************/
#include <stdlib.h> // For malloc and free
#include <stdio.h>  // For printf

/****************************************************************************
 * Hidden Definitions
 *
 * These definitions are not available outside of this file. However, because
 * the are forward declared in hash_table.h, the type names are
 * available everywhere and user code can hold pointers to these structs.
 ***************************************************************************/
/**
 * This structure represents an a hash table.
 * Use "HashTable" instead when you are creating a new variable. [See top comments]
 */
struct _HashTable
{
    /** The array of pointers to the head of a singly linked list, whose nodes
        are HashTableEntry objects */
    HashTableEntry **buckets;

    /** The hash function pointer */
    HashFunction hash;

    /** The number of buckets in the hash table */
    unsigned int num_buckets;
};

/**
 * This structure represents a hash table entry.
 * Use "HashTableEntry" instead when you are creating a new variable. [See top comments]
 */
struct _HashTableEntry
{
    /** The key for the hash table entry */
    unsigned int key;

    /** The value associated with this hash table entry */
    void *value;

    /**
     * A pointer pointing to the next hash table entry
     * NULL means there is no next entry (i.e. this is the tail)
     */
    HashTableEntry *next;
};

/****************************************************************************
 * Private Functions
 *
 * These functions are not available outside of this file, since they are not
 * declared in hash_table.h.
 ***************************************************************************/
/**
 * createHashTableEntry
 *
 * Helper function that creates a hash table entry by allocating memory for it on
 * the heap. It initializes the entry with key and value, initialize pointer to
 * the next entry as NULL, and return the pointer to this hash table entry.
 *
 * @param key The key corresponds to the hash table entry
 * @param value The value stored in the hash table entry
 * @return The pointer to the hash table entry
 */
static HashTableEntry *createHashTableEntry(unsigned int key, void *value)
{
   HashTableEntry *entry = (HashTableEntry *)malloc(sizeof(HashTableEntry));
    if (!entry) {
        return NULL;
    }
    entry->key = key;
    entry->value = value;
    entry->next = NULL;
    return entry;
}

/**
 * findItem
 *
 * Helper function that checks whether there exists the hash table entry that
 * contains a specific key.
 *
 * @param hashTable The pointer to the hash table.
 * @param key The key corresponds to the hash table entry
 * @return The pointer to the hash table entry, or NULL if key does not exist
 */
static HashTableEntry *findItem(HashTable *hashTable, unsigned int key)
{
    unsigned int bucket = hashTable->hash(key);
    HashTableEntry *entry = hashTable->buckets[bucket];

    while (entry) {
        if (entry->key == key) {
            return entry;
        }
        entry = entry->next;
    }

    return NULL;
}

/****************************************************************************
 * Public Interface Functions
 *
 * These functions implement the public interface as specified in the header
 * file, and make use of the private functions and hidden definitions in the
 * above sections.
 ****************************************************************************/
// The createHashTable is provided for you as a starting point.
HashTable *createHashTable(HashFunction hashFunction, unsigned int numBuckets)
{
    // The hash table has to contain at least one bucket. Exit gracefully if
    // this condition is not met.
    if (numBuckets == 0)
    {
        printf("Hash table has to contain at least 1 bucket...\n");
        exit(1);
    }

    HashTable *newTable = (HashTable *)malloc(sizeof(HashTable));

    newTable->hash = hashFunction;
    newTable->num_buckets = numBuckets;
    newTable->buckets = (HashTableEntry **)malloc(numBuckets * sizeof(HashTableEntry *));

    unsigned int i;
    for (i = 0; i < numBuckets; ++i)
    {
        newTable->buckets[i] = NULL;
    }

    return newTable;
}

void destroyHashTable(HashTable *hashTable)
{
    if (!hashTable) return; //

    for (unsigned int i = 0; i < hashTable->num_buckets; ++i) {
        HashTableEntry *entry = hashTable->buckets[i];
        while (entry) {
            HashTableEntry *temp = entry;
            entry = entry->next;

            if (temp->value) {
                free(temp->value);
            }

            free(temp);
        }
    }

    if (hashTable->buckets) {
        free(hashTable->buckets);
    }

    free(hashTable);
}

void *insertItem(HashTable *hashTable, unsigned int key, void *value)
{
    unsigned int bucket = hashTable->hash(key);
    HashTableEntry *existingEntry = findItem(hashTable, key);

    if (existingEntry) {
        void *oldValue = existingEntry->value;
        existingEntry->value = value;
        return oldValue;
    } else {
        HashTableEntry *newEntry = createHashTableEntry(key, value);
        newEntry->next = hashTable->buckets[bucket];
        hashTable->buckets[bucket] = newEntry;
        return NULL;
    }
}

void *getItem(HashTable *hashTable, unsigned int key)
{
   HashTableEntry *entry = findItem(hashTable, key);
    if (entry != NULL) {
        return entry->value;
    }
    return NULL;
}

void *removeItem(HashTable *hashTable, unsigned int key)
{
    unsigned int bucket = hashTable->hash(key);
    HashTableEntry **entryPtr = &(hashTable->buckets[bucket]);
    
    while (*entryPtr) {
        HashTableEntry *entry = *entryPtr;
        if (entry->key == key) {
            void *value = entry->value;
            *entryPtr = entry->next;
            free(entry);
            return value;
        }
        entryPtr = &((*entryPtr)->next);
    }

    return NULL;
}

void deleteItem(HashTable *hashTable, unsigned int key)
{
    void *value = removeItem(hashTable, key);
    if (value != NULL) {
        free(value);
    }
}