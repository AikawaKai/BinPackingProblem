
typedef struct dataset
 {
  int n;          // numero di oggetti da inserire nei bin
  int *items;     // vettore degli oggetti totali
  int *inserted;  // vettore degli oggetti inseriti nei bin
  int *to_insert; // vettore degli oggetti da inserire nei bin
} dataset;


void load_dataset(char *filename, dataset d_s);
