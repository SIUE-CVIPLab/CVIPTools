#ifndef lint
static char sccsid[] = "@(#)bilinear_prim.c 1.1 89/04/19";
#endif
/*******************************************************************************

  Title:  Bilinear interpolation primitives
  Author:  Steve Azevedo (??); modified for VIEW by Jim Brase
  Date:  Nov. 17, 1986
  Function:  Interpolates a signal by an integer factor using bilinear
             interpolation


     (c) Copyright 1987 the Regents of the University
         of California. All rights reserved.

     This work was produced at the Lawrence Livermore
     National Laboratory. The United States Government
     retains certain rights therein.


*******************************************************************************/

#define interp(a,b,c) (a+(b-a)*c)

/* assume out_h = (in_h - 1) * mul + 1 and same for w's */

int bilinear_2d_byte( in_vec , in_h , in_w , mul , out_vec , out_h , out_w )
unsigned char  * in_vec , * out_vec ;
int           in_h , in_w , mul , out_h , out_w ;


{
int i_out , j_out ;
int i_in  , j_in ;
int i_sub , j_sub ;
int temp1 , temp2;
float alpha , beta, tempa, tempb;
int   sw , se , ne , nw ;
                                                                       
if ((out_h == (in_h - 1) * mul + 1) && (out_w == (in_w - 1) * mul + 1))
   {
   for ( (j_out = 0, j_sub = 0) ; j_out < out_h * out_w ; 
         (j_out += out_w , j_sub = (j_sub < mul - 1) ? j_sub + 1 : 0 ) )
      {                                   
      j_in = ( j_out / out_w / mul ) * in_w ;
      beta = ( 1.0 * j_sub ) / mul ;

      for ( (i_out = 0 , i_sub = 0) ; i_out < out_w ; 
            (i_out++ , i_sub = (i_sub < mul - 1) ? i_sub + 1 : 0 ) )
         {
         i_in = i_out / mul ;
         alpha = ( 1.0 * i_out - i_in * mul ) / mul ;   

         sw = j_in + i_in ;             
         se = j_in + i_in + 1 ;
         nw = j_in + in_w + i_in ;
         ne = j_in + in_w + i_in + 1 ;
                                                        
         if ( j_sub == 0 )
            {
            nw -= in_w ;
            ne -= in_w ;
            }
         if ( i_sub == 0 )
            {
            ne -= 1 ;
            se -= 1 ;
            }      
	 tempa = in_vec[sw]; tempb = in_vec[se];
	 temp1 = interp ( tempa , tempb , alpha );
	 tempa = in_vec[nw]; tempb = in_vec[ne];
	 temp2  =  interp ( tempa, tempb, alpha );
         out_vec [ j_out + i_out ] =                   
            interp (temp1,temp2, beta ) ;
         }
      }
   }
else
   {
     return(-1);
   }
}



int bilinear_2d_word( in_vec , in_h , in_w , mul , out_vec , out_h , out_w )
short * in_vec , * out_vec ;
int           in_h , in_w , mul , out_h , out_w ;


{
int i_out , j_out ;
int i_in  , j_in ;
int i_sub , j_sub ;
int temp1 , temp2;
float alpha , beta, tempa, tempb;
int   sw , se , ne , nw ;
                                                                       
if ((out_h == (in_h - 1) * mul + 1) && (out_w == (in_w - 1) * mul + 1))
   {
   for ( (j_out = 0, j_sub = 0) ; j_out < out_h * out_w ; 
         (j_out += out_w , j_sub = (j_sub < mul - 1) ? j_sub + 1 : 0 ) )
      {                                   
      j_in = ( j_out / out_w / mul ) * in_w ;
      beta = ( 1.0 * j_sub ) / mul ;

      for ( (i_out = 0 , i_sub = 0) ; i_out < out_w ; 
            (i_out++ , i_sub = (i_sub < mul - 1) ? i_sub + 1 : 0 ) )
         {
         i_in = i_out / mul ;
         alpha = ( 1.0 * i_out - i_in * mul ) / mul ;   

         sw = j_in + i_in ;             
         se = j_in + i_in + 1 ;
         nw = j_in + in_w + i_in ;
         ne = j_in + in_w + i_in + 1 ;
                                                        
         if ( j_sub == 0 )
            {
            nw -= in_w ;
            ne -= in_w ;
            }
         if ( i_sub == 0 )
            {
            ne -= 1 ;
            se -= 1 ;
            }      
	 tempa = in_vec[sw]; tempb = in_vec[se];
	 temp1 = interp ( tempa , tempb , alpha );
	 tempa = in_vec[nw]; tempb = in_vec[ne];
	 temp2  =  interp ( tempa, tempb, alpha );
         out_vec [ j_out + i_out ] =                   
            interp (temp1,temp2, beta ) ;
         }
      }
   }
else
   {
     return(-1);
   }
}



int bilinear_2d_lword( in_vec , in_h , in_w , mul , out_vec , out_h , out_w )
int * in_vec , * out_vec ;
int           in_h , in_w , mul , out_h , out_w ;


{
int i_out , j_out ;
int i_in  , j_in ;
int i_sub , j_sub ;
int temp1 , temp2;
float alpha , beta, tempa, tempb;
int   sw , se , ne , nw ;
                                                                       
if ((out_h == (in_h - 1) * mul + 1) && (out_w == (in_w - 1) * mul + 1))
   {
   for ( (j_out = 0, j_sub = 0) ; j_out < out_h * out_w ; 
         (j_out += out_w , j_sub = (j_sub < mul - 1) ? j_sub + 1 : 0 ) )
      {                                   
      j_in = ( j_out / out_w / mul ) * in_w ;
      beta = ( 1.0 * j_sub ) / mul ;

      for ( (i_out = 0 , i_sub = 0) ; i_out < out_w ; 
            (i_out++ , i_sub = (i_sub < mul - 1) ? i_sub + 1 : 0 ) )
         {
         i_in = i_out / mul ;
         alpha = ( 1.0 * i_out - i_in * mul ) / mul ;   

         sw = j_in + i_in ;             
         se = j_in + i_in + 1 ;
         nw = j_in + in_w + i_in ;
         ne = j_in + in_w + i_in + 1 ;
                                                        
         if ( j_sub == 0 )
            {
            nw -= in_w ;
            ne -= in_w ;
            }
         if ( i_sub == 0 )
            {
            ne -= 1 ;
            se -= 1 ;
            }      
	 tempa = in_vec[sw]; tempb = in_vec[se];
	 temp1 = interp ( tempa , tempb , alpha );
	 tempa = in_vec[nw]; tempb = in_vec[ne];
	 temp2  =  interp ( tempa, tempb, alpha );
         out_vec [ j_out + i_out ] =                   
            interp (temp1,temp2, beta ) ;
         }
      }
   }
else
   {
     return(-1);
   }
}



int bilinear_2d_real( in_vec , in_h , in_w , mul , out_vec , out_h , out_w )
float * in_vec , * out_vec ;
int           in_h , in_w , mul , out_h , out_w ;


{
int i_out , j_out ;
int i_in  , j_in ;
int i_sub , j_sub ;
float temp1 , temp2;
float alpha , beta, tempa, tempb;
int   sw , se , ne , nw ;
                                                                       
if ((out_h == (in_h - 1) * mul + 1) && (out_w == (in_w - 1) * mul + 1))
   {
   for ( (j_out = 0, j_sub = 0) ; j_out < out_h * out_w ; 
         (j_out += out_w , j_sub = (j_sub < mul - 1) ? j_sub + 1 : 0 ) )
      {                                   
      j_in = ( j_out / out_w / mul ) * in_w ;
      beta = ( 1.0 * j_sub ) / mul ;

      for ( (i_out = 0 , i_sub = 0) ; i_out < out_w ; 
            (i_out++ , i_sub = (i_sub < mul - 1) ? i_sub + 1 : 0 ) )
         {
         i_in = i_out / mul ;
         alpha = ( 1.0 * i_out - i_in * mul ) / mul ;   

         sw = j_in + i_in ;             
         se = j_in + i_in + 1 ;
         nw = j_in + in_w + i_in ;
         ne = j_in + in_w + i_in + 1 ;
                                                        
         if ( j_sub == 0 )
            {
            nw -= in_w ;
            ne -= in_w ;
            }
         if ( i_sub == 0 )
            {
            ne -= 1 ;
            se -= 1 ;
            }      
	 tempa = in_vec[sw]; tempb = in_vec[se];
	 temp1 = interp ( tempa , tempb , alpha );
	 tempa = in_vec[nw]; tempb = in_vec[ne];
	 temp2  =  interp ( tempa, tempb, alpha );
         out_vec [ j_out + i_out ] =                   
            interp (temp1,temp2, beta ) ;
         }
      }
   }
else
   {
     return(-1);
   }
}



