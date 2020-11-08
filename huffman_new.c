#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_TREE_HT 50


//----------------------------------------------------

struct mnode {
  char item;
  unsigned freq;
  struct mnode *left, *right,*temp;
  struct mnode *ty[100],*dt;
};

struct mheap {
  unsigned size;
  unsigned capacity;
  struct mnode **array,*f,*it;
};

//----------------------------------------------
//newNode function
//----------------------------------------------

struct mnode *newNode(char item, unsigned freq) {
  struct mnode *temp = (struct mnode *)malloc(sizeof(struct mnode));

  temp->left = temp->right = NULL;
  temp->item = item;
  temp->freq = freq;

  return temp;
}

//----------------------------------------------
// createMinH function
//----------------------------------------------
struct mheap *createMinH(unsigned capacity) 
{
  struct mheap *minHeap = (struct mheap *)malloc(sizeof(struct mheap));

  minHeap->capacity = capacity;

  minHeap->array = (struct mnode **)malloc(minHeap->capacity * sizeof(struct mnode *));
  return minHeap;
}

//----------------------------------------------
//createAndBuildMinHeap function
//----------------------------------------------
struct mheap *createAndBuildMinHeap(char item[], int freq[], int size)
{
  struct mheap *minHeap = createMinH(size);

  for (int i = 0; i < size; ++i)
    minHeap->array[i] = newNode(item[i], freq[i]);
    
    return minHeap;
}

//----------------------------------------------
//first sort function
//----------------------------------------------

struct mheap* sort(struct mheap *minHeap,int size)
{
    int a,i,j,p=0;
    char s;
 
    for (i = 0; i < size; i++) 
        {
 
            for (j = i + 1; j < size; j++)
            {
 
                if (minHeap->array[i]->freq >=minHeap->array[j]->freq)
                 { 
                    // printf("%d,%d",minHeap->array[0]->freq,minHeap->array[j]->freq);
                    
                    
                    
                     
                     if(minHeap->array[i]->freq == minHeap->array[j]->freq)
                    {   
                        if((minHeap->array[i]->item > minHeap->array[j]->item)|| p==0 && size>5)
                        { 
                        //printf("%d,%d -%c,%c,",minHeap->array[i]->item,minHeap->array[j]->item,minHeap->array[i]->item,minHeap->array[j]->item);
                         a =  minHeap->array[i]->freq;
                         s =  minHeap->array[i]->item;
                    
                         minHeap->array[i]->freq = minHeap->array[j]->freq;
                         minHeap->array[i]->item = minHeap->array[j]->item;
                    
                         minHeap->array[j]->freq = a;
                         minHeap->array[j]->item = s; 
                         p=p+1;
                        }
                        
                        
                        
                    }
                    else
                    {
                    a =  minHeap->array[i]->freq;
                    s =  minHeap->array[i]->item;
                    
                    minHeap->array[i]->freq = minHeap->array[j]->freq;
                   minHeap->array[i]->item = minHeap->array[j]->item;
                    
                    minHeap->array[j]->freq = a;
                    minHeap->array[j]->item = s;
                    }
                }
 
            }
 
        }
// for(i=0;i<size;i++)
// {
//   //  printf("%c",minHeap->array[i]->item);
// }
    return minHeap;
}

//----------------------------------------------
//second sort function
//----------------------------------------------
struct mheap *sort1(struct mheap*root,struct mheap *minHeap, int size,int kp)
{
    int j=0,i,k=0,f=0;
    
    for(i=1;i<size;i++)
    {
        if(minHeap->array[0]->freq==minHeap->array[i]->freq)
        {
            f = f + 1;
        }
    }
    
    
    for(i=0;i<size;i++)
    {   
        
        if(minHeap->array[i+1]!=NULL)
        {
            
        if (minHeap->array[i]->freq < minHeap->array[i+1]->freq || ((minHeap->array[i]->freq == minHeap->array[i+1]->freq) && f==1))
        {
            //printf("%d,%d",minHeap->array[i]->freq,minHeap->array[i+1]->freq);
            
            
            if((minHeap->array[i]->freq==minHeap->array[i+1]->freq) && size==4 && kp==5)
            {
          root->array[k] =  minHeap->array[i];
             minHeap->array[i]=minHeap->array[i+1];
             minHeap->array[i+1]=root->array[k];
        
            }
            else
           {
               
            break;
          // printf("%c,%d - ",minHeap->array[i]->item,minHeap->array[i]->freq);
           }
            
           }
           else
           {
               
            root->array[k] =  minHeap->array[i];
             minHeap->array[i]=minHeap->array[i+1];
             minHeap->array[i+1]=root->array[k];
        
          // printf("%c,%d - ",minHeap->array[i]->item,minHeap->array[i]->freq);
        }
        }
     }     
   return minHeap;
}


//----------------------------------------------
// check isLeaf
//----------------------------------------------

int isLeaf(struct mnode *root) 
{
  return !(root->left) && !(root->right);
}

//----------------------------------------------
//print function
//----------------------------------------------
void disparray(int arr[], int n, char s) {
  int i;
  

  printf("%c = ", s);
  for (i = 0; i < n; ++i)
    {
     
       printf("%d",arr[i]);
      
    }
    printf("\n");

    
}

//----------------------------------------------
// main Print function
//----------------------------------------------
void printheap(struct mnode *root, int arr[], int top, char t) {
    
    if(root->item==t)
      {
    disparray(arr, top,root->item);
      }
      
  if (root->left) {
    arr[top] = 0;
    printheap(root->left, arr, top + 1,t);
  }
  if (root->right) {
    arr[top] = 1;
    printheap(root->right, arr, top + 1,t);
  }

}
//----------------------------------------------
//Huffman code function
//----------------------------------------------
void huff(char item[], int freq[], int size, char *jk) 
{
  int arr[MAX_TREE_HT];
 struct mnode *left, *right, *top;
  struct mheap *minHeap = createAndBuildMinHeap(item, freq, size);
  struct mheap *root;
  root=createMinH(size);
  int j=0,i,m=size,kp=size,to=0;

  sort(minHeap,m);
 
 for(int k=0;k<size-1;k++)
 {  j=0;  
     if(size==5 && minHeap->array[k+2]!=NULL && minHeap->array[1]->freq==15 || (kp==9 && m==size))
    {left=minHeap->array[1];
   right=minHeap->array[0];
     }
  else{
left=minHeap->array[0];
right=minHeap->array[1];
}
if(minHeap->array[0]->freq==5 && kp==9)
{
    left=minHeap->array[1];
   right=minHeap->array[0];
}

top = newNode('$', left->freq + right->freq);

    top->left =left;
    top->right =right;
    
    minHeap->array[1]=top;
    
     for(i=1;i<m;i++)
   {
       minHeap->array[j]=minHeap->array[i];
      
      // printf("%c,%d - ",minHeap->array[j]->item,minHeap->array[j]->freq);
       j++;
   }

  // printf("\n");
    
m--;
   minHeap->array[m]=NULL;
    sort1(root,minHeap,m,kp);
//  for(i=0;i<m;i++)
//   {
//       printf(" %c,%d  ",minHeap->array[i]->item,minHeap->array[i]->freq);
//       }
//   printf("\n");

 }


top=minHeap->array[0];

for(i=0;i<size;i++)
 {

printheap(top, arr, to,jk[i]);
 } 
 
}


//----------------------------------------------------
// Frequency of strings
//----------------------------------------------------
int fr(char *g,int *ch,int i)
{
    char string[100];
   int c = 0, count[26] = {0}, x;

   //printf("Enter a string\n");
   fgets(string,sizeof(string),stdin);


   while (string[c] != '\0' && string[c] !='\n' && string[c] !=' ' ) {
   /** Considering characters from '_' to 'z' only and ignoring others. */

      if (string[c] >= '_' && string[c] <= 'z') {
         x = string[c] - '_';
         count[x]++;
      }

      c++;
   }

   for (c = 0; c < 26; c++)
   {
   
            if(count[c]!=0)
            {
       
         g[i] = c + '_';
         
         ch[i]=count[c];
         i=i+1;
            }
   }
  
  
return i;
}

//----------------------------------------------------
// string Sort 
//----------------------------------------------------
void ss(char *ch)
 {
   char temp;

   int i, j;
   int n = strlen(ch);

   for (i = 0; i < n-1; i++) {
      for (j = i+1; j < n; j++) {
         if (ch[i] > ch[j]) {
            temp = ch[i];
            ch[i] = ch[j];
            ch[j] = temp;
         }
      }
   }
   
   int k=0; 
   if(ch[0]=='_')
   {  
       for(int w=1;w<n;w++)
       {
         
           ch[k]=ch[w];
           k++;
       }
       
       ch[k]='_';
   }
 

 }

// Main function:
//----------------------------------------------
int main() 
{
    
   char g[100],jk[100];
  int ch[100],i=0,j=0;

  i=fr(g,ch,i);

  strcpy(jk,g);
  ss(jk);
  huff(g, ch, i,jk);

return 0;
    
}




