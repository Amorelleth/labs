----
# Usage Examples

##Create
creates an empty set with name 'set'

    create set

##Exit
exit programme

    exit

##Show sets
prints available sets

    sets

##Help
prints command description

    help create

##Insert
insertion of value int 5 and value complex re=4 im=5
    
    set insert int 5
    set insert complex 4 5

##Print
prints set with name 'set'

    set print

##Delete
delete set with name 'set'

    set delete

delete element 'int 5' from 'set'

    set delete int 5

##Clear
clear set with name 'set'

    set clear

##Includes
check if an element 'int 5' is in 'set'

    set inclues int 5

check if a 'set2' is in 'set1'

    set1 includes set2

##Equal
check if a 'set1' is equal to the 'set2'

    set1 == set2
    set1 equal set2

##Merge
merge 'set1' and 'set2', prints result 

    set1 + set2
    set1 merge set2

merge 'set1' and 'set2' into 'set3'

    set1 + set2 set3
    set1 merge set2 set3

##Intersection
intersection of 'set1' and 'set2', prints result 
   
    set1 * set2
    set1 intersection set2

intersection of 'set1' and 'set2' into 'set3'
    
    set1 * set2 set3
    set1 intersection set2 set3

##Subtract
subtraction of 'set1' and 'set2', prints result 
    
    set1 - set2
    set1 subtract set2

subtraction of 'set1' and 'set2' into 'set3'
    
    set1 - set2 set3
    set1 subtract set2 set3
