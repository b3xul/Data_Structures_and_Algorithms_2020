#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "BST.h"

int main(int argc, char *argv[]) {
    int sel = 0, cont = 1, visit;
    char fileName[200];
    char name[MAXS];
    BST tree=NULL;
    FILE *fin, *fout;
    Item x;

    tree = NULL;

    while(cont)  {
        printf("\nOperations on the BST\n");
        printf("================\n");
        printf("\t1.Create catalogue\n");
        printf("\t2.Insert leaf\n");
        printf("\t3.Insert root\n");
        printf("\t4.Search element\n");
        printf("\t5.Search minimum price\n");
        printf("\t6.Search maximum price\n");
        printf("\t7.Show elements\n");
        printf("\t8.Show number of elements\n");
        printf("\t9: Display tree height\n");
        printf("\t10: Display number of leaves\n");
        printf("\t11.Store to file  \n");
        printf("\t12.Load from file \n");
        printf("\t0.Exit           \n");
        printf("sel: ");
        if(scanf("%d",&sel)<=0) {
            printf("Invalid selection!\n");
            exit(0);
        }
        else {
            switch(sel) {
                case 1:
                    if(tree!=NULL)
                        printf("You have to free the old one first!");
                    else{
                        tree=BSTinit();
                        if (tree == NULL)
                            exit(-1);
                    }
                break;
                case 2:
                    printf("Inserire name[char*] price[float] : ");
                    BSTinsert_leafI(tree,ITEMscan(stdin));
                break;
                case 3:
                    printf("Inserire name[char*] price[float] : ");
                    BSTinsert_root(tree,ITEMscan(stdin));
                break;
                case 4:
                    printf("Inserire name[char*] of the element: ");
                    scanf("%s", name);
                    ITEMstore(stdout,BSTsearch(tree,name));
                break;
                case 5:
                    ITEMstore(stdout, BSTmin(tree));
                break;
                case 6:
                    ITEMstore(stdout, BSTmax(tree));
                break;
                case 7:
                    printf("Select:\n-1: preorder | 0: inorder | 1: post-order | ");
                    scanf("%d",&visit);
                    BSTvisit(tree,visit);
                break;
                case 8:
                    printf("BST of %d elements\n", BSTcount(tree));
                break;
                case 9:
                    printf("BST of height=%d\n", BSTheight(tree));
                break;
                case 10:
                    printf("BST of %d leaves\n", BSTleaves(tree));
                break;
                case 11:
                    printf("Input file name: ");
                    scanf("%s", fileName);
                    fout = fopen(fileName, "w");
                    if (fin != NULL) {
                        BSTvisit2(tree, PREORDER,fout,0);
                        fclose(fout);
                    }
                break;
                case 12:
                    printf("Input file name: ");
                    scanf("%s", fileName);
                    fin = fopen(fileName, "r");
                    if (fin != NULL) {
                        while( ITEMcheckNull (x=ITEMscan(fin)) ==0 )
                            BSTinsert_leafI(tree, x);
                        fclose(fin);
                    }
                    //BSTvisit2(tree, PREORDER,stdout,0);
                break;
                case 0:
                    cont = 0;
                    BSTfree(tree);
                    free(tree);
                break;
                default:    printf("Invalid option\n");
            }
        }
    }
    return 0;
}
