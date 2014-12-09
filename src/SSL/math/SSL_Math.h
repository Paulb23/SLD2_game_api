/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Math.h
   @author  P. Batty
   @brief   Implements a useful Maths / physics functions

   This module implements useful Math / physics functions
*/
/*--------------------------------------------------------------------------*/

#ifndef SSL_MATH_H_
#define SSL_MATH_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Ray traces between two points
  @param    x0			  Starting x position
  @param    y0			  Starting y postion
  @param	x1			  Ending x positon
  @param	y1			  Ending y positon
  @param	data		  data to pass to the call back function
  @param    func		  Function pointer
  	  	  	  	  	  	  	  @param int	x position currently checking
  	  	  	  	  	  	  	  @param int	y position current checking
  	  	  	  	  	  	  	  @param void	data passe in previously
  	  	  	  	  	  	  	  @return 0 on no collision 1 on collision
  @return 1 if something is in the way else 0

  Scans between the two given points in a strait line calling the function pointer
  with the current x and y coordinates to check, the function should return 1 if the
  x,y point has hit something else 0.

\-----------------------------------------------------------------------------*/
int SSL_Raytrace(int x0, int y0, int x1, int y1, void *data, int(*func)(int, int, void *));

#endif
