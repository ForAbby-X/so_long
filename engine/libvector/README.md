
# C-VECTORLIB

The vector lib is a simple and easy to use c library adding c++ like vectors.

exemple:
```c
{
	t_vector	my_vector;
	int		my_object;
	
	my_object = 10;

	my_vector = vector_create(sizeof(int));
	//Allocate and initialised all the memory used by the vector, 
	//returns a pointer to itself or 'NULL' if there is an error.
	//The parameter is the size of the storage type.

	vector_add(&vector, &my_object);
	//Add an object at the end of the vector and returns it.
	//Please note that the object memory is copied.
	//The growth factor of the vector is x1.5.
	
	vector_get(&vector, 0u);
	//Returns an object at a certain index in the vector.

	vector_pop(&vector, &my_object);
	//Remove the object at the end of the vector and returns it.
	
	vector_destroy(&vector);
	//Free all the memory used by the vector.
}
```
