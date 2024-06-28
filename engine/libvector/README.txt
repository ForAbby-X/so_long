
+-------------+
| C-VECTORLIB |
+-------------+

The vector lib is a simple and easy to use c library adding c++ like vectors.

exemple:

{
	t_vector	*my_vector;
	int			my_object;
	
	my_object = 10;

	my_vector = vector_create(1);	//Allocate  and initialised all the memory used by the vector, it returns a pointer to it.
										//The parameter is the base size that is malloc'ed at the creation of he vector,
										//that means that the vector is still considered empty.

	vector_add(vector, &my_object);	//Add an object at the end of the vector and returns it.
										//(note that the growth of the vector is exponential, its max_size is multiplied by 2)

	vector_get(vector, 0);			//Returns an object at an index in the vector.

	vector_pop(vector, &my_object);	//Remove the object at the end of the vector and returns it.
	
	vector_destroy(vector);			//Free all the memory used by the vector.
}
