[settings] backgroundColour=green textColour=blue textSpeed=0.01
[notsettings] should not ignore
[begin] This is the story of a <choice val="man-man/woman-woman"/>. It starts on the road after a long long day... What happens if we have multiple choices? <choice branch="it crashes-[branch1]/things are fine-[branch2]/we deviate for women\'s sake-[option1]-woman"/>. We'll find out! Filling the screen. <font colour="255,0,0,255"> Filling the screen. </font> Filling the screen.

<text option="This is shown because you picked man.-man"/>

<text variant="This is shown because you picked crashes.-[branch1]/This is shown because you didnt pick crashes."/>

Filling the screen. <font colour="blue"> Filling the screen. </font> <set speed="0.005"> Filling the screen faster. Filling the screen. Filling the screen. Filling the screen. Filling the screen. </set> <set speed="0.02"> Filling the screen slower. </set> Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. <image background="red"> Filling the screen. Filling the screen. Filling the screen. </image> Filling the screen. Filling the screen. Filling the screen.

<set speed="0.005"> Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen. Filling the screen.
[branch1] Test to see if speed passes over or is reset after choice branch <choice branch="the end-[end]"/>.
[branch2] Test2 <choice branch="the end-[end]/or a loop-[option1]"/>.
[option1] An option <choice branch="the end-[end]/or a loop-[branch2]"/>.
[end] This is the end.
