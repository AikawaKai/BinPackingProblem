
typedef struct dataset
 {
  char name[255]; // case test name
  int n;          // numero di oggetti da inserire nei bin
  int bin_size;   // grandezza del bin
  int best_sol;   // miglior soluzione fino ad ora
  int *items;     // vettore degli oggetti totali
  int *inserted;  // vettore degli oggetti inseriti nei bin
  int *to_insert; // vettore degli oggetti da inserire nei bin
} dataset;


void load_dataset(char *filename, dataset *d_s);
