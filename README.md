# Show-Case-And-Deep-Learning
Move an objet 3d in function of how the client looks. Sould be use in a shop window.

Deep learning analyses the position of the head and store it in 7 categories :
- Client is Closed
- Client is  Far
- Client is  Right 
- Client is  Left
- Client is  Up
- Client is  low
   
Then, a programm in C++, with a OpenGL context, receive messages by OSC that contains the category.
After that, the C++ program moves the object in fonction the client's position :
- Closed/Far -> Zoom out / Zoom
- Right/Left -> spin horizontally
- Up/Low -> spin verticaly

# Demonstration in real-time
![](gif(2).gif)
