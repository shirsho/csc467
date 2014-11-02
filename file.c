{
	/*  This is valid program, because you can call
      float dp3(vec3,vec3);
      as a term inside an expression, as done in line 8
  */
  vec4 x = vec4(1.0, 2.0, 3.0, 4.0); 
  vec4 f = vec4(1.0, 3.0, 5.0, 7.0) + lit(x); 
}
