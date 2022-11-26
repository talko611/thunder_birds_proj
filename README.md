# thunder_birds_proj
Console app inspired by thunder birds game (Cpp course MTA)

Notes:

#Changed small ship maximum weight can push to 3 (to make stage 3 more interesting).

#Game is implemented with colors.

#All objects which will fall to into a "hole"(means out of the valid screen) will die.

########################### Stage 3 #################################################

steps file:

-contains only direction for wandring ghosts(first row) and the active ship direction.

-if there are space of a line between the rows its because there are no wandring ghost in the specific screen

-values: directions(left, right etc.) ,switch keys(big ,small) and unvalid key/stop mode (null)

result file:

-contains only 2 values time exit round and result of the round(if the player played on more then one life you will see the same amount of times played in the result file for the specific screen)

last game deatails file:

-contains the last mode the game was played and the number of the file started from

