void ED(char x[], char y[], int row, int col){


    // initialize
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
        	
            c[i][j] = 0;
            b[i][j] = 0;
        }
    }

    
    for(int i=0; i<row; i++){
        c[0][i] = i; 
        b[0][i] = -2;
    }
    for(int i=0; i<row; i++){
        c[i][0] = i; 
        b[i][0] = -1;
    }


    // calculation
    for(int i=1; i<row; i++){

        for(int j=1; j<col; j++){
            
            int subs = c[i-1][j-1];
            int del = c[i-1][j];
            int insert = c[i][j-1];
            
            if(x[i] == y[j]){
                c[i][j] = c[i-1][j-1];
                b[i][j] = UNCHANGED;
                
            }

            else{

            	int m1 = min(subs, del);
            	int minimum = min(m1, insert);

                //cout << x[i] << " " << y[j] << endl;
                if (minimum == subs){

                	// min = substitute
                    c[i][j] = c[i-1][j-1]+1;
                    b[i][j] = SUBSTITUE;
                    //cout << "SUBSTITUTE\n";
                       
                    
                }

                else if (minimum == c[i][j-1]){
                        // min = insert
                        c[i][j] = c[i][j-1]+1;
                        b[i][j] = INSERT;
                        //cout << "INSERT\n";
                }

                else{
                    
                    // min = del
                    c[i][j] = c[i-1][j]+1;
                    b[i][j] = DELETE;
                    //cout << "DEL\n";
                }
            }
        }
    }
}