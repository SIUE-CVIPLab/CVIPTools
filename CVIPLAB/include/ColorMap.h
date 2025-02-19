
/*
 * RGB Color Class Stuff
 */

#if !defined( COLOR_DEFINED )

   #define COLOR_DEFINED

   struct ColorType {
      byte r, g, b;
   };

   typedef struct ColorType Color;

   #define getRed_Color(p) ((p).r)
   #define getGrn_Color(p) ((p).g)
   #define getBlu_Color(p) ((p).b)

   #define assign_Color(p,red,grn,blu) do { (p).r = (red); (p).g = (grn); (p).b = (blu); } while ( 0 )

   #define equal_Color(p,q) ( (p).r == (q).r && (p).g == (q).g && (p).b == (q).b )

#endif

/*
 * Color Histogram/Mapping Class Stuff
 */

#if !defined( COLOR_HISTOGRAM_DEFINED )

   #define COLOR_HISTOGRAM_DEFINED

   #define RED 0
   #define GRN 1
   #define BLU 2

   struct ColorHistObjectType {
      Color pixel;
      unsigned value;
   };

   typedef struct ColorHistObjectType ColorHistObject;

   struct ColorHistogramType {
      ColorHistObject *histogram;
      unsigned no_of_colors;
   };

   typedef struct ColorHistogramType ColorHistogram;

   typedef ColorHistObject *ColorMap;

   typedef HashTable ColorHashTable;

   extern ColorHistogram *new_ColorHist(void);
   extern void delete_ColorHist(ColorHistogram *chP);
   extern void compute_ColorHist(ColorHistogram *chP, Image *imageP, unsigned maxval);
   extern void print_ColorHist( ColorHistogram *chP );
   extern int dropColor_ColorHist( ColorHistogram *chP, Color pixel, unsigned *no_pixels);

#endif

/*
 * Color Hash Table Class Stuff
 */


#if !defined( COLOR_HASHTABLE_DEFINED )

   #define COLOR_HASHTABLE_DEFINED

   #define new_ColorHT() new_HT((size_t)20023)
   #define setKey_ColorHT(h,k) setKey_HT(h,k)

   extern void addObject_ColorHT(HashTable *chtP, Color pixel, int index);
   extern ColorHashTable *hist2Hash_ColorHT(ColorHistogram *chP);
   extern int lookUpColor_ColorHT( ColorHashTable *chtP, Color pixel );
   extern void delete_ColorHT(ColorHashTable *chtP);

#endif
