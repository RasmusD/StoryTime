[settings]
[begin] How Original - Bænkebidere
By: Rasmus Dall
Illustrations: 666the999 <choice branch="/[intro]"/>
[intro] Rottefanger, job <choice val="choose equipment/equipment"/> <choice branch="/[approach]"/>
[approach] <choice branch="return to get equipment-[intro]-!equipment/set some traps-[setTraps]-traps/use poison-[poison]-poison"/>
[setTraps] you set some traps. <choice branch="/[end]"/>
[poison] you use some poison. <choice branch="/[end]"/>
[end] the end.