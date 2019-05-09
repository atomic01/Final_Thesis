// r g b 0 0 0 je crna a r g b 255 255 255 je bijela
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "qdbmp.h"

typedef struct Graph;
typedef struct Graph *Node;
struct Graph{


    bool visited;
    short int r;
    short int g;
    short int b;
    short int x;
    short int y;
    short int numberOfNeighbours;
    short int numberOfMadeConnections;

    short int distanceToUp;
    short int distanceToDown;
    short int distanceToLeft;
    short int distanceToRight;
    double distanceToEnd;

    Node nextUp;
    Node nextDown;
    Node nextLeft;
    Node nextRight;
};

typedef struct List;
typedef struct List *Pos;
struct List{

    Node node;
    double combinedDistance;
    double totalPathLenght;

    bool pathViaLeftNeighbour;
    bool pathViaRightNeighbour;
    bool pathViaUpNeighbour;
    bool pathViaDownNeighbour;

    char path[1000];

    Pos next;
};

#include "Declarations.h"
#include "GraphFunctions.h"
#include "StackFunctions.h"

Node createGraphFromBMP( BMP* );

int main(int argc, char* argv[])
{
    const char* filename = "growingtree.bmp";
    BMP* bmp;
    Node Graph= createNode();
    Pos Path=createPos();

    bmp = BMP_ReadFile( filename );

    Graph=createGraphFromBMP( bmp );
    Path=findShothestPathUsingAstar(Graph, bmp);
    TracePathInBMPFile(bmp, Path);

    BMP_WriteFile( bmp, "result.bmp");
    BMP_Free( bmp );

    return 0;
}

Node createGraphFromBMP( BMP* bmp)
{
    Node Graph = createNode();
    Node startNode = createNode();
    Node endNode = createNode();

    startNode=findStartNode(bmp);
    endNode=findEndNode(bmp);

    Graph=colorAllTheNodesToGreen(bmp, startNode, endNode);
    Graph=generateGraphFromBMPAlgorithm(bmp, startNode, endNode);

    return Graph;
}

Pos findShothestPathUsingAstar( Node Graph , BMP* bmp)
{
    Pos priority_queue= createPos();
    Pos path = createPos();
    Pos FirstOnPriorityQueue=NULL;
    Node startNode = Graph;

    priority_queue=PushStartNodeToPriorityQueue(priority_queue, startNode);

    while(priority_queue->next->node->distanceToEnd!=0)
    {
       FirstOnPriorityQueue=PopFront(priority_queue);
       FirstOnPriorityQueue->next=NULL;
       priority_queue=expandFirstOnPriorityQueue(priority_queue, FirstOnPriorityQueue);
    }

    priority_queue->next->next=NULL;

    path=generatePath(priority_queue->next, startNode);

    return path;
}

void TracePathInBMPFile(BMP* bmp , Pos path )
{
    Pos P=path->next;
    short int i=0;

    resetMazeColors(bmp);

    while(P->node->distanceToEnd!=0)
    {
        if(P->next->pathViaUpNeighbour==true)
            for(i=0; i < P->node->distanceToDown;i++)
                BMP_SetPixelRGB( bmp, P->node->x , P->node->y+i ,255, 0, 0);
        else if(P->next->pathViaDownNeighbour==true)
            for(i=0; i < P->node->distanceToUp;i++)
                BMP_SetPixelRGB( bmp, P->node->x , P->node->y-i ,255, 0, 0);
        else if(P->next->pathViaRightNeighbour==true)
            for(i=0; i < P->node->distanceToLeft;i++)
                BMP_SetPixelRGB( bmp, P->node->x-i , P->node->y ,255, 0, 0);
        else if(P->next->pathViaLeftNeighbour==true)
            for(i=0; i < P->node->distanceToRight;i++)
                BMP_SetPixelRGB( bmp, P->node->x+i , P->node->y ,255, 0, 0);

        P=P->next;
    }

    BMP_SetPixelRGB( bmp, P->node->x , P->node->y ,255, 0, 0);
}


