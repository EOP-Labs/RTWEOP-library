'Rome: Total War - Alexander' console commands list: 

Number: 0
add_money
add_money <opt:faction_type> <amount> : adds an amount of money to a faction's coffers, can be negative, default is player faction

Number: 1
add_population
add_population <settlement_name> <amount> : adds an amount of population to a settlement, can be negative

Number: 2
adjust_sea_bed
adjust_sea_bed : adjusts whole sea bed to specified height

Number: 3
ai_turn_speed
ai_turn_speed <multiplier> : sets the maximum speed of turn processing during the ai round

Number: 4
amdb_max
amdb_max : sets aerial map overlay depth bias for max zoom

Number: 5
amdb_min
amdb_min : sets aerial map overlay depth bias for min zoom

Number: 6
amdb_offset
amdb_offset : sets aerial map overlay offset towards camera

Number: 7
auto_win
auto_win <attacker/defender>: the attacker or defender wins the next autoresolved battle

Number: 8
bestbuy
bestbuy : sells units cheaper

Number: 9
bounds
bounds : toggle display of bounding objects

Number: 10
building_debug
building_debug: 
toggles building debug mode. 
  TAB to toggle view modes, RIGHT SHIFT-TAB to reset mode, LEFT SHIFT-TAB to go back modes.  
  G damages mouse-over building.  P displays plaza.


Number: 11
burn_piggies_burn
burn_piggies_burn  <on/off> : ignite all the piggy winks

Number: 12
capture_settlement
capture_settlement <settlement name> : evicts any resident characters and armies and gives the settlement to the local player

Number: 13
character_reset
character_reset : resets the character back to it's start of turn settings

Number: 14
clear_messages
Clear all the current stacked messages

Number: 15
control
control <faction_type> : switches player control to specified faction; old faction may not act correctly as ai faction

Number: 16
create_building
create_building <settlement_name> <building_level_id> : creates a building of the specified type in a settlement; for building level id's see export_descr_building.txt

Number: 17
create_unit
create_unit <settlement/character_name> <unit_id> <opt:how_many> <opt:exp/armour/weapon>: creates one or more units of the specified type

Number: 18
damage_wall
damage_wall <settlement> <gate> <breach>: 
Damage wall of settlement.  Forces 40% damage to a random gatehouse and a nearby straight section. Destroys gatehouse if 'gate' parameter present; breaches wall if 'breach' present


Number: 19
date
date <year> : changes the campaign date to the given year

Number: 20
diplomacy_mission
diplomacy_mission <ai_faction> <target_faction> <mission_type> <opt:mission_target> : creates a diplomacy mission

Number: 21
diplomatic_stance
diplomatic_stance <faction_a> <faction_b> <allied/neutral/war>: 
Set the diplomatic stance between the two factions


Number: 22
disable_ai
disable_ai [opt: tac | sub | dip | name]: disables all (default) or part of the ai for all factions

Number: 23
event
event <event_type> <opt:position> : creates an event at position

Number: 24
filter_coastlines
filter_coastlines : applies filter to world map coastlines

Number: 25
fire
fire (mt | toggle | reload | int)

Number: 26
force_battle_defeat
force_battle_defeat : forces the local player's alliance to win the battle, completely destroying the enemy alliance

Number: 27
force_battle_victory
force_battle_victory : forces the local player's alliance to win the battle, completely destroying the enemy alliance

Number: 28
force_diplomacy
force_diplomacy <accept/decline/off>: 
Forces the negotiator to accept or decline a proposition


Number: 29
give_ancillary
give_ancillary <charactername> <ancillary name> : gives the character an ancillary

Number: 30
give_trait
give_trait <charactername> <trait name> <opt:level>: gives the character a trait at level (default = level 1)

Number: 31
give_trait_points
give_trait_points <charactername> <trait name> <points>: gives the character points for trait

Number: 32
halt_ai
halt_ai <opt:factiontypename> : halts the turn sequence just before the start of the specified faction's turn, or the current faction if no faction given

Number: 33
ie
ie <reload>


Number: 34
invulnerable_general
invulnerable_general <character_name> : makes that named general invulnerable in battle

Number: 35
jericho
jericho : and the walls came a-tumblin' down

Number: 36
kill_army
kill_army <character_name><opt:dont_show_death_anim> : kills an army commanded by a character with the given name

Number: 37
kill_character
kill_character <character_name> : kills a character with the given name

Number: 38
kill_faction
kill_faction <faction_type> : removes the faction from the game

Number: 39
lights
lights : <merge> <used> <auto>

Number: 40
list_ancillaries
list_ancillaries : lists all the available ancillaries

Number: 41
list_characters
list_characters <opt:faction_type> : lists all the characters in the world or those belonging to a faction

Number: 42
list_traits
list_traits : lists all the available traits

Number: 43
list_units
list_units <character/settlement name> : lists all of the units in an army, with details.

Number: 44
message_collation_set
Set the message collation on or off (sets all factions)

Number: 45
move_character
move_character <name> <x>,<y> : moves named character to position on campaign map

Number: 46
mp
mp <charactername> <amount>: gives the character movement points

Number: 47
nw_stats
nw_stats: 
toggles display of network stats.


Number: 48
oliphaunt
oliphaunt : the biggest around

Number: 49
output_unit_positions
output_unit_positions <filename> : output the positions of all units in the battle to the specified file

Number: 50
perf_times
Toggle display of simple performance times of game update vs display

Number: 51
process_cq
process_cq <settlement>: 
Completes all (possible) construction pending in queue


Number: 52
process_rq
process_rq <settlement>: 
Completes all (possible) recruitment pending in queue


Number: 53
puppify_my_love
??????

Number: 54
reapply_rigid_model_influence


Number: 55
regenerate_radar
regenerate_radar: Does what it says on the tin

Number: 56
reload_shaders
reload_shaders : reloads all vertex shaders

Number: 57
reload_textures
reload_textures : reloads all textures

Number: 58
reset_display
reset_display: 
Forces a display_close(); display_open() display reset cycle


Number: 59
run_ai
run_ai [opt:x]: re-starts an ai turn sequence after disableai or haltai has been triggered; 
use x to also re-enable all parts of the ai which have been individually disabled

Number: 60
season
season <season> : changes the campaign season to the given season

Number: 61
set_building_health
set_building_health <settlement_name> <building_chain> <final health percent>: 
sets health of a building of the specified type (eg core_building) 
in a settlement, so that the final health percentage is as specified; for building chains see export_descr_building.txt

Number: 62
set_ranking_interval
set_ranking_interval : sets the denominator of the faction ranking graph interval which is calculated as (number_of_turns / denominator).  If set to 0, then the denominator will be set to number_of_turns, giving an interval of 1

Number: 63
shadow
shadow <toggle/next/prev>


Number: 64
show_all_messages
Show all messages to all factions (on/off)

Number: 65
show_battle_circle
show_battle_circle <x> <y> <r> <t> : display a circle at (x, y) of r radius for t seconds

Number: 66
show_battle_line
show_battle_line <x1> <y1> <x2> <y2> <t> : display a line from (x1, y1) to (x2, y2) for t seconds

Number: 67
show_battle_marker
show_battle_marker <x> <y> <t> : display a marker at (x, y) for t seconds

Number: 68
show_battle_paths
show_battle_paths : show all valid processed paths in the pathfinder

Number: 69
show_battle_paths_for_unit
show_battle_paths_for_unit <unit_id> <time>: show all valid processed paths in the pathfinder for a specific unit given a unit id

Number: 70
show_battle_street_plan
show_battle_street_plan : show the street plan for the settlement

Number: 71
show_cursorstat
show_cursorstat : shows the cursor position and region id

Number: 72
show_landings
show_landings <opt:cursor/region_id> : shows the landing positions available to the ai from a given region, default hides them

Number: 73
show_terrain_lines
show_terrain_lines <duration> : display defensive terrain features

Number: 74
show_ui
Toggles the UI on or off as per the show_ui script command

Number: 75
surrender_regions
surrender_regions <opt: horde> <opt:faction_type> : gives all this faction's regions to the slaves. "horde" surrenders regions for all factions that can be hordes

Number: 76
test_ancillary_localisation
adds all ancillary to the character info display
ancillaries aren't actually added to the character

Number: 77
test_message
Test the event message specified in descr_event_enums.txt

Number: 78
test_network_scroll
test_network_scroll <is host (true/false)>

Number: 79
test_victory_scroll
test_victory_scroll <faction victor> <short campaign (true/false)>: 
Opens up the victory scroll declaring that the given faction is the victor
If no faction is declared then the 'timeout' scroll is displayed

Number: 80
toggle_chat_log
toggle_chat_log : shows  or hides the multiplayer chat window

Number: 81
toggle_coastlines
toggle_coastlines : toggles strategy map coastline display

Number: 82
toggle_flowing_water
toggles display of campaign map flowing water

Number: 83
toggle_fow
toggle_fow : toggles the fog of war on or off

Number: 84
toggle_game_update
toggle_game_update

Number: 85
toggle_overlay
toggle_overlay: 



Number: 86
toggle_perfect_spy
toggle_perfect_spy : toggles everyone's spying ability to perfect and infinite range, and off again

Number: 87
toggle_pr
toggle_pr: 
toggles pr mode.


Number: 88
toggle_restrictcam
toggle_restrictcam : toggles camera restrictions on or off

Number: 89
toggle_terrain
toggle_terrain <opt:region/tiletype/climate/choke/landing/frontier/features/frontier_defend> : toggles the terrain to display various data sets, no param resets to normal

Number: 90
toggle_tow
toggle_tow : shows/hides the tabbed output window

Number: 91
toggle_underlay
toggle_underlay: 



Number: 92
trigger_advice
triggers an advice thread


Number: 93
upgrade_effect
upgrade_effect <unit_id> : triggers unit upgrade effect

Number: 94
victory
victory <faction> <short>: show victory message for faction for short or long campaign.

Number: 95
vulnerable_general
vulnerable_general <character_name> : makes that named general vulnerable in battle (turns off invulnerabilty

Number: 96
write_ui_cache
write_ui_cache: writes out the ui texture cache to disk

Number: 97
zoom
zoom : zooms to specified aerial map zoom

Number: 98
zoom_to_unit
zoom_to_unit : zoom the camera to a unit of a specific id



