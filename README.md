## AP2 PROJECT 2019
### Documentation

The information provided is divided into five sections:
1. Class Point
2. Class ConvexPolygon
3. Polygon_Calculator
4. Tests
5. Compilation
6. Additional notes and aclarations

## 1. Class Point

### Useful information

* **Quadrance**: x<sup>2</sup> + y<sup>2</sup>, see we are not taking square roots here.
* **Slope**
* **Quadrant**: Tells in which quadrant you are (1,2,3,4) or 5 if you are in the axis.
* **Distance**: Returns the distance to some point.
* **Clockwise**: Tells if the angle of rotation from one point to another is positive. **_Observe I'm calling clockwise what caucasian people call counterclockwise_**, try not to be confused. From now on, the terminology will be mathematical:
  - Positive sense of rotation
  - Negative sense of rotation

### Operations
 Each operation can be interpreted as done to the point P(x,y) or to the vector OP. The available operations are the following:
* **Addition**: Represented with + or +=.
* **Substraction**: Represented with - or -=.
* **Negation**: The unary operator -.
* **Multiplication**: There are three different types:
  1. **By a scalar**:  Represented with *= and saved in the Point itself.
  2. **Vectorial product**: Represented with ^, returns the modul and sign of the vectorial product.
  3. **Dot product**: Represented with *.
* **Equality**: Represented with ==.

## 2. Class ConvexPolygon

### Attributes
1. **Hull**: It is a vector of the consecutive points of the convex hull starting at the left-most one and going in the positive direction of rotation.

 [Example][polygon]
2. **Color**: A vector with three doubles representing the colors Red, Green, and Blue. With values from 0 to 1.

### Public Methods and Operators
* **Intersection**: Represented by *. Returns the intersection of two convex polygons.
  - Cost: O(n log(m))
  - Algorithm

   For each side compute the cross points of the other polygon with the line it represents.
   Then, from the cross points and the vertices select the two that are contained by the other two.
   Finally, add all the points created in this process.
* **Union**: Represented by +. Returns the convex union of two convex polygons.
  - Cost: O((m+n)log(m+n))
  - Algorithm

   Just call the constructor of the class with all the points.
* **Bounding Box(bbox)**: Returns a rectangle (convex polygon) that contains all the given convex polygons.
  - Cost: O(n)
  - Algorithm

   Compute the minimum and maximum x-y coordinates.
   From them create the LL, LR, UR, UL corners.
   Finally, call the constructor with those four points.
* **isInside**: Tells if a convex polygon is inside another.
  - Cost: O(n log(m))
  - Algorithm

   For each point check if it is inside the polygon. If one point is not inside the program ends.
* **num_vert**: Returns the number of vertices.
* **num_edges**: Returns the number of edges.
* **area / perimeter / centroid**: Returns the area / perimeter / centroid.
* **isRegular**: Tells if a polygon is regular.
  - Cost: O(n)
  - Algorithm

   First, check if all the edges are equal.  
   Then, if all the angles are the same.
   Everything is done with a tolerance of 1%, which means that two magnitudes are equal if they differ in less than 1% of its magnitude.


### Private Methods
