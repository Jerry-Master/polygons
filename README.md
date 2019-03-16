## AP2 PROJECT 2019
### Documentation

The information provided is divided into five sections:
1. Class Point
2. Class ConvexPolygon
3. Polygon_Calculator
4. Tests
5. Compilation

## 1. Class Point

You can obtain some useful information:

* **Quadrance**: x<sup>2</sup> + y<sup>2</sup>, see we are not taking square roots here.
* **Slope**
* **Quadrant**: Tells in which quadrant you are (1,2,3,4) or 5 if you are in the axis.
* **Distance**: Returns the distance to some point.
* **Clockwise**: Tells if P1^P2 is positive. **_Observe I'm calling clockwise what caucasian people call counterclockwise_**, try not to be confused.

Furthermore, it supplies all the operations one would encounter for points, but also for vectors. Each operation can be interpreted as done to the point P(x,y) or the vector OP. The available operations are the following:
* **Addition**: Represented with + or +=.
* **Substraction**: Represented with - or -=.
* **Negation**: The unary operator -.
* **Multiplication**: There are three different types:
  1. **By a scalar**:  Represented with *=
  2. **Vectorial product**: Represented with ^, returns the modul and sign of the vectorial product.
  3. **Dot product**: Represented with *.
* **Equality**: Represented with ==.
