Pos createPos()
{
    Pos newPos = (Pos )malloc(sizeof(struct List));

    newPos->node=createNode();
    newPos->next = NULL;

    newPos->combinedDistance=32767;
    newPos->totalPathLenght=0;
    memset(newPos->path,'0',1000);

    newPos->pathViaLeftNeighbour=false;
    newPos->pathViaRightNeighbour=false;
    newPos->pathViaUpNeighbour=false;
    newPos->pathViaDownNeighbour=false;

    return newPos;
}

Pos PushList(Pos list, Node node)
{
    Pos P=list;
    Pos newPos=createPos();
    newPos->node=node;


    while(P->next!=NULL && node->y > P->next->node->y)
        P=P->next;
    while(P->next!=NULL && node->x > P->next->node->x && node->y == P->next->node->y)
        P=P->next;

    newPos->next=P->next;
    P->next=newPos;

    return list;
}

Pos PushToBack(Pos path, Pos newOnPath)
{
    Pos P = path;

    while(P->next!=NULL)
        P=P->next;

    P->next=newOnPath;

    return path;
}

Pos PopFront(Pos list)
{
    Pos P=list->next;

    if(P->next==NULL)
        list->next=NULL;
    else
        list->next=P->next;

    return P;
}

Pos getLastMember(Pos path)
{
    Pos P=path->next;
    Pos prev = path;

    while(P!=NULL)
    {
        P=P->next;
        prev=prev->next;
    }

    return prev;
}

void PrintList(Pos list)
{
    Pos P=list;
    int i=1;

    while(P->next!=NULL)
    {
        P=P->next;
        printf("%d.\t- x: %d   \ty: %d \n\tLeft:%d  Right:%d  Up:%d  Down:%d Susjedi: %d  End: %f  Path:%s\n\n",i, P->node->x, P->node->y, P->node->distanceToLeft,P->node->distanceToRight, P->node->distanceToUp, P->node->distanceToDown, P->node->numberOfNeighbours,P->node->distanceToEnd,P->path);

        i++;
    }


    printf("\n\n----------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
}

Pos PushStartNodeToPriorityQueue(Pos priority_queue, Node startNode)
{
    Pos new=createPos();

    startNode->visited=true;
    new->node=startNode;
    new->combinedDistance=startNode->distanceToEnd;
    new->totalPathLenght=0;

    priority_queue->next=new;


    return priority_queue;
}

Pos PushToPriorityQueue(Pos priority_queue, Pos new)
{
    Pos P = priority_queue;
    bool isInserted=false;

    if(P->next==NULL)
        P->next=new;
    else
    {
        while(isInserted==false)
        {
            if(P->next!=NULL && new->combinedDistance >= P->next->combinedDistance )
                P=P->next;
            else
            {
                new->next=P->next;
                P->next=new;
                isInserted=true;
            }
        }
    }

    return priority_queue;
}

Pos expandFirstOnPriorityQueue(Pos priority_queue, Pos FirstOnPriorityQueue)
{

    Pos NewOnPriorityQueue = createPos();

    int i = 0;
    while( FirstOnPriorityQueue->path[i]!='0')
        i++;
    //provjera jel postoji ako postoji jeli bio posjecen susjed ljevo
    if(FirstOnPriorityQueue->node->nextLeft!=NULL && FirstOnPriorityQueue->node->nextLeft->visited==false && FirstOnPriorityQueue->node->distanceToLeft!=32767)
    {
        NewOnPriorityQueue = createPos();
        NewOnPriorityQueue->node = FirstOnPriorityQueue->node->nextLeft;
        NewOnPriorityQueue->node->visited=true;
        NewOnPriorityQueue->pathViaRightNeighbour=true;
        NewOnPriorityQueue->totalPathLenght=FirstOnPriorityQueue->totalPathLenght + FirstOnPriorityQueue->node->distanceToLeft;
        NewOnPriorityQueue->combinedDistance=NewOnPriorityQueue->node->distanceToEnd + NewOnPriorityQueue->totalPathLenght;
        strcpy(NewOnPriorityQueue->path,FirstOnPriorityQueue->path);
        NewOnPriorityQueue->path[i]='L';

        priority_queue=PushToPriorityQueue(priority_queue, NewOnPriorityQueue);
    }
    //provjera jel postoji ako postoji jeli bio posjecen susjed desno
    if(FirstOnPriorityQueue->node->nextRight!=NULL && FirstOnPriorityQueue->node->nextRight->visited==false && FirstOnPriorityQueue->node->distanceToRight!=32767)
    {
        NewOnPriorityQueue = createPos();
        NewOnPriorityQueue->node = FirstOnPriorityQueue->node->nextRight;
        NewOnPriorityQueue->node->visited=true;
        NewOnPriorityQueue->pathViaLeftNeighbour=true;
        NewOnPriorityQueue->totalPathLenght=FirstOnPriorityQueue->totalPathLenght + FirstOnPriorityQueue->node->distanceToRight;
        NewOnPriorityQueue->combinedDistance=NewOnPriorityQueue->node->distanceToEnd + NewOnPriorityQueue->totalPathLenght;
        strcpy(NewOnPriorityQueue->path,FirstOnPriorityQueue->path);
        NewOnPriorityQueue->path[i]='R';

        priority_queue=PushToPriorityQueue(priority_queue, NewOnPriorityQueue);

    }
    //provjera jel postoji ako postoji jeli bio posjecen susjed gore
    if(FirstOnPriorityQueue->node->nextUp!=NULL && FirstOnPriorityQueue->node->nextUp->visited==false && FirstOnPriorityQueue->node->distanceToUp!=32767)
    {
        NewOnPriorityQueue = createPos();
        NewOnPriorityQueue->node = FirstOnPriorityQueue->node->nextUp;
        NewOnPriorityQueue->node->visited=true;
        NewOnPriorityQueue->pathViaDownNeighbour=true;
        NewOnPriorityQueue->totalPathLenght=FirstOnPriorityQueue->totalPathLenght + FirstOnPriorityQueue->node->distanceToUp;
        NewOnPriorityQueue->combinedDistance=NewOnPriorityQueue->node->distanceToEnd + NewOnPriorityQueue->totalPathLenght;
        strcpy(NewOnPriorityQueue->path,FirstOnPriorityQueue->path);
        NewOnPriorityQueue->path[i]='U';

        priority_queue=PushToPriorityQueue(priority_queue, NewOnPriorityQueue);
    }
    //provjera jel postoji ako postoji jeli bio posjecen susjed dole
    if(FirstOnPriorityQueue->node->nextDown!=NULL && FirstOnPriorityQueue->node->nextDown->visited==false && FirstOnPriorityQueue->node->distanceToDown!=32767)
    {
        NewOnPriorityQueue = createPos();
        NewOnPriorityQueue->node = FirstOnPriorityQueue->node->nextDown;
        NewOnPriorityQueue->node->visited=true;
        NewOnPriorityQueue->pathViaUpNeighbour=true;
        NewOnPriorityQueue->totalPathLenght=FirstOnPriorityQueue->totalPathLenght + FirstOnPriorityQueue->node->distanceToDown;
        NewOnPriorityQueue->combinedDistance=NewOnPriorityQueue->node->distanceToEnd + NewOnPriorityQueue->totalPathLenght;
        strcpy(NewOnPriorityQueue->path,FirstOnPriorityQueue->path);
        NewOnPriorityQueue->path[i]='D';

        priority_queue=PushToPriorityQueue(priority_queue, NewOnPriorityQueue);
    }



    return priority_queue;
}

Pos generatePath(Pos endPos, Node startNode)
{
    Pos path=createPos();
    Node N = startNode;
    int i = 0;

    Pos newPos=createPos();
    newPos->node=startNode;//postavljanje prvog clana
    path->next=newPos;

    Pos P=path->next;

    while( endPos->path[i]!='0')
    {
        if(endPos->path[i]=='D')
        {
            newPos=createPos();
            newPos->node=N->nextDown;
            newPos->pathViaUpNeighbour=true;
            P->next=newPos;

            N=N->nextDown;
        }
        else if(endPos->path[i]=='U')
        {
            newPos=createPos();
            newPos->node=N->nextUp;
            newPos->pathViaDownNeighbour=true;
            P->next=newPos;

            N=N->nextUp;
        }
        else if(endPos->path[i]=='L')
        {
            newPos=createPos();
            newPos->node=N->nextLeft;
            newPos->pathViaRightNeighbour=true;
            P->next=newPos;

            N=N->nextLeft;
        }
        else if(endPos->path[i]=='R')
        {
            newPos=createPos();
            newPos->node=N->nextRight;
            newPos->pathViaLeftNeighbour=true;
            P->next=newPos;

            N=N->nextRight;
        }

    P=P->next;
    i++;
    }


    return path;
}






