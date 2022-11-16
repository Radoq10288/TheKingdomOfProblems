/* File:         src/map.h
 *
 * Author:       
 *
 * Date & time:  11/04/2022-11:01:17-PM
 */

#ifndef MAP_H
#define MAP_H


#include <stdbool.h>


typedef struct {
	char army;
	int controlled_regions;
}Faction;


typedef struct {
	int region_number;
	bool contested;
	int occupying_army_count;
}Region;


typedef struct Kingdom {
	Faction factn;
	Region regn;
}Kingdom;


/* This function is only a helper function for the seek_armies_in_region()
 * to fully explore every region in the map.
 *
 * Return:
 * If function succeeds, returns zero else, returns non-negative value if
 * *map* parameter is NULL.
 */
int explore_the_map(
		char **map,				// The 2D array map.
		size_t const row_size,	// The size of the 2D array map in its x-axis.
		size_t const col_size,	// The size of the 2D array map in its y-axis.
		Kingdom *kngdm			// Output: This will contain the list of army that is found in each region.
);


/* Sorts out armies that resides in the same region and from different
 * regions.
 *
 * Return:
 * If function succeeds returns zero else, returns non-negative value if
 * *kngdm* parameter is NULL.
 */
int sort_out_armies(Kingdom *kngdm);


/* Prints out status report on how many regions each army occupies and how
 * many regions are contested.
 *
 * Return:
 * If function succeeds returns zero else, returns non-negative value if
 * *kngdm* parameter is NULL.
 */
int print_kingdom_report(Kingdom *kngdm, size_t const row_size, size_t const column_size);


/* For debugging purposes only.
 *
 * Prints details of each factions found in every region.
 *
 * This is the list of details it prints.
 * - faction
 * - CR(Controlled Regions)		The number of regions controlled by a faction.
 * - RN(Region Number)			To identify what region each faction found belong.
 * - C(Contested)				To identify if a faction belongs to a contested region.
 * - OAC(Occupying Army Count)	To identify how many faction resides in a region.
 */
int print_faction_list(Kingdom *kngdm);

#endif //MAP_H_INCLUDED


