//DECLARATIONS FOR THE GRAPH FUNCTIONS
void resetMazeColors(BMP* );
Node createNode();
Node findStartNode( BMP* );
Node findEndNode( BMP* );
Node colorAllTheNodesToGreen(BMP* , Node , Node );
Node generateGraphFromBMPAlgorithm(BMP* , Node , Node );
Node generateNodeData(BMP*, Node);
bool areTheyReallyRowNeighbours(BMP*, Node , Node );
bool areTheyReallyColumnNeighbours(BMP*, Node , Node );
Pos findShothestPathUsingAstar( Node, BMP*);


//DECLARATIONS FOR THE LIST FUNCTIONS
Pos createPos();
Pos PushList(Pos , Node );
//Node PopList(Pos , short int, short int);
void PrintList(Pos );
Node findAndConnectToNeighbours(BMP* ,Pos , Node);
void removeNodeFromList( Pos  , Node  );
Pos PushToPriorityQueue(Pos , Pos );
Pos PushStartNodeToPriorityQueue(Pos , Node);
Pos expandFirstOnPriorityQueue(Pos ,Pos);
Pos PopFront(Pos );
Pos PushToBack(Pos , Pos );
void TracePathInBMPFile(BMP* , Pos );
Pos getLastMember(Pos );
Pos generatePath( Pos , Node);


//GENERAL FUNCTIONS
double potency(int x, int y)
{
    double result=1;

    for(y;y>0;y--)
        result = result * x;

    return result;
}
























