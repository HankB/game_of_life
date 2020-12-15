# Notes

place to record durrent efforts and thoughts so that when I set this aside for a couple months, I know what I was trying to do when I come back.

## 2020-12-14

Fix duplicate definitrion of `MyFrame::OnShow()`. What was I trying to accomplish when I put that in?

Problem: scrolling the screen makes multiple artifacts on the display. (Will address later)

Problem: mapping GoL grid coordinates to screen coordinates screwed up. Fixed, but needs cleanup. Lots of debug code included at present.

GoL -> screen mapping cleaned up. Good enough for now.

Back to scrolling... Resizing the screen works fine. Scrolling, not so much. About popup refreshes the screen, apparently igfnoring the scrolled position.

Next? Create a real GoL grid and display on screen.