/********************************************************************
	Here below we define static arrays containing vector height, 
	width, entries.
*******************************************************************/
   /* VQ_15: 10 frequency bands 10  compression ratio: 14.37*/
   static int VQ_15_vector_height[] = {64, 2, 2, 2, 2, 2, 2, 4, 4, 4};
   static int VQ_15_vector_width[] = {64, 2, 2, 2, 2, 2, 2, 4, 4, 4};
   static int VQ_15_vector_entries[] = {3, 1024, 1024, 512, 512, 512, 256, 128, 128, 128};
   
   /* VQ_PCT_15 (PCT): 10 frequency bands,  30 sub imgs compression ratio: 15.12*/
   static int VQ_PCT_15_vector_height[] = {	/*R band*/64, 2, 2, 2, 2, 2, 2, 4, 4, 4, 
   					/*G band*/64, 2, 2, 2, 2, 2, 2, 4, 4, 4, 
   					/*B band*/64, 2, 2, 2, 2, 2, 2, 4, 4, 4};
   static int VQ_PCT_15_vector_width[] = {	/*R band*/64, 2, 2, 2, 2, 2, 2, 4, 4, 4, 
   					/*G band*/64, 2, 2, 2, 2, 2, 2, 4, 4, 4, 
   					/*B band*/64, 2, 2, 2, 2, 2, 2, 4, 4, 4};
   static int VQ_PCT_15_vector_entries[] = {	/*R band*/1, 1024, 1024, 512, 512, 512, 256, 128, 128, 64, 
   					/*G band*/1, 256, 256, 64, 64, 64, 64, 0, 0, 0,
   					/*B band*/ 1, 256, 256, 64, 64, 64, 64, 0, 0, 0};

   /* VQ_30: 10 frequency bands 10 compression ratio: 31.69*/
   static int VQ_30_vector_height[] = {64, 2, 2, 2, 2, 2, 2, 4, 4, 4};
   static int VQ_30_vector_width[] = {64, 2, 2, 2, 2, 2, 2, 4, 4, 4};
   static int VQ_30_vector_entries[] = {3, 256, 256, 128, 64, 64, 64, 0, 0, 0};
   
   /* VQ_PCT_30 (PCT): 10 frequency bands,  30 sub imgs compression ratio: 31.36*/
   static int VQ_PCT_30_vector_height[] = {	/*R band*/64, 2, 2, 2, 2, 2, 2, 4, 4, 4, 
   					/*G band*/64, 2, 2, 2, 2, 2, 2, 4, 4, 4, 
   					/*B band*/64, 2, 2, 2, 2, 2, 2, 4, 4, 4};
   static int VQ_PCT_30_vector_width[] = {	/*R band*/64, 2, 2, 2, 2, 2, 2, 4, 4, 4, 
   					/*G band*/64, 2, 2, 2, 2, 2, 2, 4, 4, 4, 
   					/*B band*/64, 2, 2, 2, 2, 2, 2, 4, 4, 4};
   static int VQ_PCT_30_vector_entries[] = {	/*R band*/1, 256, 256, 128, 64, 64, 64, 16, 16, 16, 
   					/*G band*/1, 32, 32, 16, 16, 16, 0, 0, 0, 0,
   					/*B band*/ 1, 32, 32, 16, 16, 16, 0, 0, 0, 0 };
   					
   /* VQ_55: 10 frequency bands 10 compression ratio: 54.48*/
   static int VQ_55_vector_height[] = {64, 2, 2, 2, 4, 4, 4, 4, 4, 4};
   static int VQ_55_vector_width[] = {64, 2, 2, 2, 4, 4, 4, 4, 4, 4};
   static int VQ_55_vector_entries[] = {3, 32, 32, 8, 4, 4, 0, 0, 0, 0};
   
   /* VQ_PCT_55 (PCT): 10 frequency bands,  30 sub imgs compression ratio: 56.15*/
   static int VQ_PCT_55_vector_height[] = {	/*R band*/2, 2, 2, 2, 4, 4, 4, 4, 4, 4, 
   					/*G band*/2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 
   					/*B band*/2, 2, 2, 2, 2, 2, 2, 4, 4, 4};
   static int VQ_PCT_55_vector_width[] = {	/*R band*/2, 2, 2, 2, 4, 4, 4, 4, 4, 4, 
   					/*G band*/2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 
   					/*B band*/2, 2, 2, 2, 2, 2, 2, 4, 4, 4};
   static int VQ_PCT_55_vector_entries[] = {	/*R band*/1024, 128, 128, 64, 32, 32, 8, 0, 0, 0, 
   					/*G band*/512, 16, 16, 16, 0, 0, 0, 0, 0, 0,
   					/*B band*/ 512, 16, 16, 16, 0, 0, 0, 0, 0, 0 };
   /* VQ_80: 10 frequency bands 10 compression ratio: 81.09*/
   static int VQ_80_vector_height[] = {2, 2, 2, 2, 2, 2, 2, 4, 4, 4};
   static int VQ_80_vector_width[] = {2, 2, 2, 2, 2, 2, 2, 4, 4, 4};
   static int VQ_80_vector_entries[] = {1024, 128, 128, 32, 4, 4, 0, 0, 0, 0};
   
   /* VQ_PCT_80 (PCT): 10 frequency bands,  30 sub imgs compression ratio: 78.09*/
   static int VQ_PCT_80_vector_height[] = {	/*R band*/2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 
   					/*G band*/2, 2, 2, 2, 4, 4, 8, 16, 16, 16, 
   					/*B band*/2, 2, 2, 2, 4, 4, 8, 16, 16, 16};
   static int VQ_PCT_80_vector_width[] = {	/*R band*/2, 2, 2, 2, 2, 2, 4, 4, 4, 8, 
   					/*G band*/2, 2, 2, 2, 4, 4, 8, 16, 16, 16, 
   					/*B band*/2, 2, 2, 2, 4, 4, 8, 16, 16, 16};
   static int VQ_PCT_80_vector_entries[] = {	/*R band*/1024, 128, 128, 16, 16, 16, 0, 0, 0, 0, 
   					/*G band*/256, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   					/*B band*/ 256, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   /* VQ_set: 10 frequency bands 10 default as VQ_30*/
   static int VQ_set_vector_height[] = {64, 2, 2, 2, 2, 2, 2, 4, 4, 4};
   static int VQ_set_vector_width[] = {64, 2, 2, 2, 2, 2, 2, 4, 4, 4};
   static int VQ_set_vector_entries[] = {3, 256, 256, 128, 64, 64, 64, 0, 0, 0};
   
   /* VQ_PCT_set (PCT): 10 frequency bands,  30 sub imgs default as VQ_PCT_30*/
   static int VQ_PCT_set_vector_height[] = {	/*R band*/64, 2, 2, 2, 2, 2, 2, 4, 4, 4, 
   					/*G band*/64, 2, 2, 2, 2, 2, 2, 4, 4, 4, 
   					/*B band*/64, 2, 2, 2, 2, 2, 2, 4, 4, 4};
   static int VQ_PCT_set_vector_width[] = {	/*R band*/64, 2, 2, 2, 2, 2, 2, 4, 4, 4, 
   					/*G band*/64, 2, 2, 2, 2, 2, 2, 4, 4, 4, 
   					/*B band*/64, 2, 2, 2, 2, 2, 2, 4, 4, 4};
   static int VQ_PCT_set_vector_entries[] = {	/*R band*/1, 256, 256, 128, 64, 64, 64, 16, 16, 16, 
   					/*G band*/1, 32, 32, 16, 16, 16, 0, 0, 0, 0,
   					/*B band*/ 1, 32, 32, 16, 16, 16, 0, 0, 0, 0 };
   					
