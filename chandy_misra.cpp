#include <bits/stdc++.h>
using namespace std;

bool dependencies[100][100];//={{0,0,1,0,0},{1,0,0,1,0},{0,1,0,0,1},{0,0,0,0,0},{0,0,0,0,0}};
map<int,int>pp;
int V=0;

bool dfsutil(int initiator,int sender,bool visited[],bool recstack[],vector<int>&path)
{
        visited[sender]=true;
        recstack[sender]=true;



        for(int i=0; i<V; i++)
        {
                if(dependencies[sender][i]&&!visited[i])
                {
                        cout<<"Probe "<<"("<<initiator+1<<","<<sender+1<<","<<i+1<<")"<<endl;
                        path.push_back(i+1);
                        if(dfsutil(initiator,i,visited,recstack,path))
                                return true;
                        path.pop_back();
                }
                else if(dependencies[sender][i]&&recstack[i])
                {
                        cout<<"Probe "<<"("<<initiator+1<<","<<sender+1<<","<<i+1<<")"<<endl;
                        cout<<"Initiator id="<<i+1<<","<<"Reciever Id="<<i+1<<endl;
                        return true;
                }
        }
        recstack[sender]=false;
        return false;
}
bool dfs(int src)  //ids of initiator,sender,receiver
{
        int j,k;
        bool visited[V],recstack[V];
        for(int i=0; i<V; i++)
                visited[i]=false;

        vector<int>path; //to check if local cycle or not
        path.push_back(src);

        bool cycle=dfsutil(src,src,visited,recstack,path);

        if(!cycle)
        {
                cout<<"No Cycle"<<endl;
                return false;
        }
        else
        {
                int f=1;
                for(int i=0; i<path.size(); i++)
                {
                        for(int j=i+1; j<path.size(); j++)
                        {
                                if(pp[i]!=pp[j])
                                {
                                        f=0;
                                        break;
                                }
                        }
                }
                if(f==1)
                {
                        cout<<"Local Cycle Detected"<<endl;
                        return false;
                }
                else
                        cout<<"Cycle Detected"<<endl;
        }
        return true;
}

void readfile( char arg1[], char arg2[])
{
        FILE *file1,*file2;
        file1=fopen(arg1,"r");
        file2=fopen(arg2,"r");
        int dependency_var,site_var;
        int count_lines;
        while (EOF != (count_lines=getc(file1)))
                if ('\n' == count_lines)
                        ++V;
        fseek(file1, 0, SEEK_SET);
        fscanf (file1, "%d", &dependency_var);
        while (!feof (file1))
        {
                for(int i=0; i<V; i++)
                        for(int j=0; j<V; j++)
                         {
                                dependencies[i][j]=dependency_var;
                                fscanf (file1, "%d", &dependency_var);
                        }
        }
        fscanf (file2, "%d", &site_var);
        while (!feof (file2))
        {
                for(int i=0; i<V; i++)
                {
                        pp[i]=site_var;
                        fscanf (file2, "%d", &site_var);
                }
        }
        fclose(file1);
        fclose(file2);

}

int main( int argc, char* argv[] )
{

/*
   READ FROM FILES
   FIRST FILE->READ DEPENDENCIES
   EG:
      S1 S2 S3
   S1 1   0  1
   S2 1   1  0
   S3  0  0  0

   SECOND FILE-->READ MAPPING FROM PROCESSNUMBER TO SITE NO
 */
// pid and site pairs

        //pp[0]=0;
        //pp[1]=0;
        //pp[2]=1; //change this to 0 for local cycle!
        //pp[3]=2;
        //pp[4]=1;

        readfile(argv[1],argv[2]);
        int src=0;
        if(dfs(src))
                cout<<"Deadlock detected"<<endl;
        else
                cout<<"No Deadlock"<<endl;
}
