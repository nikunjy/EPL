### Move Semantics 
Remember how we discussed copy and shallow copy. Move is something similar but move literally moves the owneship of the contents from one object to another. 
Here is how you write move semantics for the string class: 
``` 
 String(String&& x) { 
 	//do whatever with x
 } 
 //but don't use x after this 
``` 
* Move basically renders the object that was "moved" as useless. Anything goes after the move has been invoked.  
* Use move with temporary variables which are going to be destructed anyway. 
```  
 String s(String()); 
``` 
* To invoke explicitly use std::move, it is sort of a typecast for the compiler to know that we want to move this object.