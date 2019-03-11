# Writing a Story

StoryTime is not just a game, it is a framework or an interpreter as well. In fact, almost more so than a game. But don't tell those who just "plays" the game. It can take any, well-formed, Story and render it as beautiful mesmerising two dimensional screen real estate filled with `image boxes`, `text boxes` and `choice boxes`. *\*Appreciation of artistic style may vary.*

This document describes how *you* can join the fabled ranks of the StoryTellers. Aka ***Those who write***.

Now, don't get your nose in the air just yet. Your Stories might still be terrible and unworthy. But they **might** just be the most amazing stories since Jules Verne. Or Kafka. Orwell, Pratchett or Dall. Probably not. But at least you tried, and it will probably be a better try than this wry guide.

### So, how to become a StoryTeller?

It's pretty simple really.

You run the StoryWriter application which will guide you through the process with an interactive tutorial, a drag-and-drop style interface, real-time previews of your story and snug cuddly Teddybears to hug when you need inspiration.

Or, that is, once I've implemented that application you can. See TODO. *\*Teddybears not included.*

So until that fantasy becomes reality, you've got to content with this terrible guide. I mean, it's like 2 headlines, 7 paragraphs and 5 bad jokes in and you _still_ don't know what the hell is going on.

Let's get to that part.

You want to write a story. Here's how:

1. Open a new text file.

2. Write a Story. Name it `name.story`.

3. Put it in a directory called `name` in the `stories` folder.

4. If you've mad eyour own imagery and wish to use it. Put it in a folder called `images` in the directory where you put `name.story`.

5. Run StoryTime and select ***your*** creation to play in the menu.

6. If it's really good, you can share it with us or your remaining friends. No pressure.

Of steps 1-6 only 2 should cause you any headache. If 1, 3, 4, 5 or 6 is hard to understand. This guide will not help you. Sorry. Not sorry.

### How to do the magical bit in 2

You're probably not surprised by this point that I feel the need to point out to you that all the headaches you may get from coming up with a Story is purely on you. StoryTimeCorp and it's non-existing affiliates take no responsibility for your suffering as a consequence of being an aspiring writer. We'll take all the credit when you succeed though.

A Story is simply a text file containing a number of segments. It might be helpful to open the `test.story` file now and have a gander at it and possibly have it open as we go along.

There is three required segments in a Story.

[begin] marks the beginning of the Story and will be the first segment displayed.

[end] marks the end of the Story and will be the last segment displayed.

[settings] details any non-default settings of the Story and can be empty.

Note how each segment ***must***, and I'm not kidding, start with a name enclosed in square brackets followed by a space. Weird shit happens or the whole thing just doesn't work if you don't do this.

Secondly, any segment which is not either [end] or [settings] - which includes [begin] - must contain at least one <choice> markup which tells the StoryTime interpreter what the name of the next segment to go to should be. If that doesn't exist. Well, then we can't reach The End can we?

If all of the above is followed, your Story should *just work* when put through the interpreter.

In case it doesn't or you just want to test it without opening the whole application, then see it fail and then try again. A handy little helper application exist called `StoryVerifier`. It does what it says on the tin. You pass a Story to it and it then tells you if this Story is good to go. Or not, and hopefully also why not if not.

### But how does markup work?

Good question. Lemme just see   Um   it's sorta, kinda, maybe like XML?

Basically, if you want to apply markup you just do the following:

\<markupCategory categoryType="value"> some text \</markupCategory\>

The first bit is the opening bracket. It tells you what markup to apply on the following bit of text. It is recognised by the `<` character - anything following this character is treated as markup until a `>` character appears. Within this the first bit is the markup category this markup belongs to, followed by a whitepace then the naem of the categoryType of the markup, an equals sign and the value it should be set to. Then the closing `>`.

Side note, if you want to write a `<` in your Story you want to use the escape character `\` before it. Else the interpreter thinks this is markup. This isn't necessary for the `>` character unless you for some unfathomable reason want that within some markup.

You technically don't ***need*** the closing markup. Without it, whatever markup you set will just continue until you set something else.

There's also self-contained markup. They look like this:

\<markupCategory categoryType="value"/\>

They don't modify anything continously but have some sort of immediate effect. Like making the player make a choice. Pretty essential.

Take a look at the test.story for examples of **every** available markup in action. Or look below for an exhaustive list:

\<choice\> things to do with choices and the most complicated markup as there's markup within the markup. Meta.
* val - *self-contained* - a choice which does not affect the Story's branching but which saves a value which can be referred to later to enable other choices.
   
   The value field of this is a bit complicated and has a specific format. Ignore this format at your own peril. Format is:
   `choice1` then `/` then `choice2` for as many choices as is needed. You can also just have a single choice if you want to save some value no matter what (maybe you get a glove in two different branches which enables a choice in a third branch).
   A choice has the format of `choice text` then `-` then `variableName`. `choice text` is the text to be displayed on screen when making the choice (and in the main story after). `variableName` is the *single word no whitespace* variable to save.
   Note that the term variable is kinda misleading as this really is just telling the interpreter that you've made a "choice" called this name. That's it. So don't use [] here to avoid name clashes. Using a variable multiple times is fine, it'll only be stored once though, and it can't be removed later.
* branch - *self-contained* - a choice which decides the next segment in the story. Counter-intuitively this does not need to have more than one choice. If only one choice is present then this just sets what the next segment is without the player seeing it. Useful for splitting segments into smaller more manageable bits. Though normally, you'd totally have an actual choice to make. Format:
   
   `choice1` then `/` then `choice2` for as many choices as intended.
   A choice has a slightly expanded format to the \<choice val\> markup which is `choice text` then `-` then `[branchName]` then `-` then `variableName`. The last two are optional. I.e. first provide the text to show, then the name of the branch this choice leads to, then an **optional** variable to save for later use. So both `choice text-[branchName]-variableName` and `choice text-[branchName]` are valid.

\<font\> things to do with fonts
* colour - *opened and closed* - yup that's colour with a ***u***. Deal with it. Basically you can change the colour of the font.
   
   The value can be *either* a comma separated list of RGB values *or* from a set of preset values named: black, white, red, green, blue, yellow, magenta, cyan and transparent. *\* Any similarity to the list of preset colour values from SFML is purely intended.*

\<image\> things to do with images
* background - *opened and closed* - change the background colour of the story. Some day in the distant future, or maybe tomorrow if I can be arsed, this could be an actual image!
   
   The value is the same sort of colo***u***r thing as for the font colour value. That is   drum roll for repetition: The value can be *either* a comma separated list of RGB values *or* from a set of preset values named: black, white, red, green, blue, yellow, magenta, cyan and transparent. *\* Any similarity to the list of preset colour values from SFML is purely intended.*
* display - *opened and closed* - set the/an image to be displayed with the story. ***THIS DOES NOTHING rigHT NOW***
   
   The value will be some sort of path to the image.

\<set\> set some settings
* speed - *opened and closed* - change the text speed.
   
   The value is some number. You'd probably make it around 0.01 which seems a reasonable starting point. I don't remember which makes it faster and which slower. But hey - try it. Actually   less is faster.

\<text\> a piece of text which depends on previous choices
* option - *self-contained* - some text which is only shown if a previous choice/variable has been made/exists.
   
   The value field has the format of `text` then `-` then `variableName`. The `text` is the text to show if the `variableName` has previously been saved or chosen.
* variant - *self-contained* - some text which will vary depending on previous choices.
   
   The value field has the format of `variant1` then `/` then `variant2` then `-` then `variableName` and then more `/variantX-variableName` as you need.
   Note that `variant1` is the default and will thus be showed if no other variants variables are present. If no default variant is defined, nothing will be shown if no variable is previously chosen. The first found variable that has been chosen previously is displayed. So watch the order.

And that's all there is to say about markup. At least right now, see TODO for loads more planned.

### But I could set some settings and you didn't explain those

True. [settings] is a whitespace delimited list of `thingToSet` then `=` then `value`. The available settings are:

* textColour - set the default colour of the text as per the colour way. REPETITION: The value can be *either* a comma separated list of RGB values *or* from a set of preset values named: black, white, red, green, blue, yellow, magenta, cyan and transparent. *\* Any similarity to the list of preset colour values from SFML is purely intended.*
* backgroundColour - set the default colour of the background as per the colour way. No. No mere repetitions. You better know by now.
* textSpeed - set the default speed of the text. I may have mentioned this before. But 0.01 is a good starting value. Less is faster.

And that's it! Now, go make Stories!