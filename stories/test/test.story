[settings] backgroundColour=black textColour=white textSpeed=0.02 displayImage=testImage.jpg
[notsettings] should not ignore but should not appear anywhere
[begin] This is a test story to demonstrate all the various features of the StoryTime story writing framework.
By Rasmus Dall
You don't see this visually, but this is a segment which just goes straight to another segment without a choice. If you look at the actualy marked up story, you'll see what I mean. In fact, for this story to make sense a lot of the time you want to look at the story file. It's really for people writing stories. Also, this segment is called "[begin]" - which will always be the first segment of the story shown, even if it's not the first in the story file.<choice branch="-[seg1]"/>
[seg1] In this segment you have to make a choice between cake and cookies.
You chose <choice val="cake-cake/cookies-cookies"/>.
This choice is remembered and different text can be shown depending on the choice:
<text option="This is shown because you picked cake.-cake"/>
<text option="This is shown because you picked cookies.-cookies"/>
That could also happen in a later segment but does not determine which way the overall story goes in any immediate sense. Though it could affect which choices are available later, and also what text appears.
Now, let's make a "branching" choice. This means that depending on what you choose, the story will divert in different directions.
So, pick:
<choice branch="left-[left]/right-[right]"/>
[left] You went left. You're dead. Kidding...<choice branch="-[seg2]"/>
[right] You went right. You survived. Barely...<choice branch="-[seg2]"/>
[seg2] Ok, the above text looked like the non-branching choice, but underneath something entirely different happened which has many different implications. For example non-branching choices in the left branch would not necessarily be in the right branch but would carry over to future branches. Whereas a non-branching choice in a branch will always appear.
Except when it's optional.
Like in this choice:
<choice branch="Go left-[left]/Go right-[right]/continue-[seg3]/COOKIES!-[coke]-cookies/CAKE!-[coke]-cake"/>.
Here you can see a looping choice - you can go back to the left or right previous branches (just because it says so in the text doesn't mean it's that way - it is here though... or is it?), or you can continue, or something weird involving edible things all depending on your different edible things.
[coke] <text variant="CAKE!!!-cake/COOKIE!!!"/>
The above is actually a text variant depending on your previous choices, if you picked CAKE or COOKIES before it'll show different things. But that's it, it'll just show different things and continue wihtout affecting the general story branches.<choice branch="-[seg3]"/>
[seg3] <text variant="This is shown because you picked continue and not one of the edible things./This is another text variant, so I\'m not saying anymore."/>

Anyway, lets show something else.
There's a picture above. <image display="testImage2.jpg">That can change. For a period. </image>Or it can be done permanently. E.g. by not closing the markup as here now.<image display="testImage2.jpg"> Just by changing the markup value like now<image display="testImage.jpg"> you can override another setting. If you close it later, it will cancel the most recent change.</image> This is general for all markups which can be closed (see manual).
You can <font colour="blue">change the font colour.</font>
<set speed="0.05">You can also change the text speed ot be slower. <set speed="0.005"> Or faster faster faster faster faster faster faster faster.</set></set>
<image background="red"/>You can change the background colour.</image>
And that's really it right now.<choice branch="-[end]"/>
[end] This is the end. This segment is called "[end]" which is always the last segment. If it this and the "[begin]" segment doesn't exist, the story won't work.
If you want help making the story work you can run the StoryVerifier which will tell you if it should work. It's helpful when writing, I promise.