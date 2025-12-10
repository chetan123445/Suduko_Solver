#include<stdio.h>
#include<math.h>

//This function check whether the i is suitable at that place or not
int isSafe(int n,int grid[][n],int row,int col,int i)
{
    // If we find a same number in that row, we return 0;
    for(int j=0;j<n;j++)
    {
        if(grid[row][j]==i)
        {
            return 0;
        }
    }
 
    // If we find a same number in that column, we return 0;
    for(int j=0;j<9;j++)
    {
        if(grid[j][col]==i)
        {
            return 0;
        }
    }
 
    // If we find a same number in it's 3*3 matrix, we return 0;
    int row_of_3x3=row-(row%((int)sqrt(n))); 
    int col_of_3x3=col-(col%((int)sqrt(n)));
    for(int y=row_of_3x3;y<(row_of_3x3+(int)sqrt(n));y++)
    {
        for(int z=col_of_3x3;z<(col_of_3x3+(int)sqrt(n));z++)
        {
            if(grid[y][z]==i)
            {
                return 0;
            }
        }
    }
    return 1;
}


int Solve(int n,int grid[][n],int row,int col)
{
    if(row==n-1 && col==n)
    {
        return 1;
    }
     
    if(col==n)
    {
        row++;
        col=0;
    }
    
    //If the current position already contains value>0,then we move to the next column
    if(grid[row][col]>0)
    {
        return Solve(n,grid,row,col+1);
    }
    
    for(int i=1;i<=n;i++)
    {
        if(isSafe(n,grid,row,col,i)==1) 
        {
            grid[row][col]=i;
            if (Solve(n,grid,row,col+1)==1)
                return 1;
        }
        // Removing the assigned i,since our assumption was wrong and we go for next assumption with diff i value
        grid[row][col]=0;
    }
    return 0;
}


int main()
{
    int n=9;
    int grid[n][n];
    printf("                       INPUT\n");
    printf("                       =====\n\n");
    printf("Enter the data of suduko(For empty space-use 0):\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d",&grid[i][j]);
        }
    }
    
    printf("\nSuduko entered by your side is:\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        { 
            printf("|");
            printf("%d",grid[i][j]);
            printf("|  ");
        }
        printf("\n");
        for(int i=0;i<n;i++)
        {
            printf("-----");
        }
        printf("\n");
    }
    
    printf("\nSolved Suduko is as follows:\n");
    if(Solve(n,grid,0,0)==1)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            { 
                printf("|");
                printf("%d",grid[i][j]);
                printf("|  ");
            }
            printf("\n");
            for(int i=0;i<n;i++)
            {
                printf("-----");
            }
            printf("\n");
        }
    }
    else
    {
        printf("No Solution exists\n");
    }
}