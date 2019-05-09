void resetMazeColors(BMP* bmp)
{
    UINT    width, height;
    UCHAR   r, g, b;

    short int i = 0;
    short int j = 0;

    width = BMP_GetWidth( bmp );
    height = BMP_GetHeight( bmp );

    for( j; j <= height; j++)
    {
        i = 0;
        for( i; i <= width; i++)
        {
            BMP_GetPixelRGB( bmp, i, j, &r, &g, &b );
            if(r != 0 || g != 0 || b != 0)
                BMP_SetPixelRGB( bmp, i, j ,255, 255, 255);
        }
    }
}

Node createNode()
{
    Node newNode = (Node)malloc(sizeof(struct Graph));

    newNode->visited = false;
    newNode->r = 255;
    newNode->g = 255;
    newNode->b = 255;
    newNode->x = 0;
    newNode->y = 0;

    newNode->numberOfNeighbours=0;
    newNode->numberOfMadeConnections=0;

    newNode->distanceToUp=32767;//inace bi bilo beskonacnost, ali ovo je najveci short int broj
    newNode->distanceToDown=32767;
    newNode->distanceToLeft=32767;
    newNode->distanceToRight=32767;
    newNode->distanceToEnd=32767;


    newNode->nextUp = NULL;
    newNode->nextDown = NULL;
    newNode->nextLeft = NULL;
    newNode->nextRight = NULL;

    return newNode;
}

Node findStartNode( BMP* bmp)
{
    UINT    width;
    UCHAR   r, g, b;
    UINT    x, y;
    Node start = createNode();
    short int i = 0;

    width = BMP_GetWidth( bmp );
    while( i < width)
    {
        BMP_GetPixelRGB( bmp, i, 0, &r, &g, &b );
        if( r == 0 && g == 0 && b == 0)
            i++;
        else if(r == 255 && g == 255 && b == 255)
        {
            start->x = i;
            start->y = 0;
            i=width;
        }
    }

    BMP_SetPixelRGB( bmp, start->x, 0 , 0, 255, 0 );


    return start;

}

Node findEndNode( BMP* bmp)
{
    UINT    width, height;
    UCHAR   r, g, b;
    UINT    x, y;
    Node end = createNode();
    short int i = 0;

    width = BMP_GetWidth( bmp );
    height = BMP_GetHeight( bmp );

    while( i < width)
    {
        BMP_GetPixelRGB( bmp, i, height -1, &r, &g, &b );
        if( r == 0 && g == 0 && b == 0)
            i++;
        else if(r == 255 && g == 255 && b == 255)
        {
            end->x = i;
            end->y = height -1;
            i=width;
        }
    }

    BMP_SetPixelRGB( bmp, end->x, end->y , 0, 255, 0 );


    return end;

}

Node colorAllTheNodesToGreen(BMP* bmp, Node startNode, Node endNode)
{
    UINT    width, height;
    UCHAR   r, g, b;
    UCHAR   rLeft, gLeft, bLeft;
    UCHAR   rRight, gRight, bRight;
    UCHAR   rUp, gUp, bUp;
    UCHAR   rDown, gDown, bDown;
    UINT    x, y;
    short int i = 1;//razlog je jer nije potrebno pregledavati prvi stupac jer je to zid a start imamo
    short int j = 1;//razlog je jer nije potrebno pregledavati prvi redak jer je zid a start imamo

    width = BMP_GetWidth( bmp );
    height = BMP_GetHeight( bmp );
    width--;//razlog je jer nije potrebno pregledavati zadnji stupac jer je to zid a end imamo
    height--;//razlog je jer nije potrebno pregledavati zadnji redak jer je zid a end imamo

    for( j; j < height; j++)
    {
        i = 1;
        for( i; i < width; i++)
        {
            BMP_GetPixelRGB( bmp, i, j, &r, &g, &b );
            BMP_GetPixelRGB( bmp, i-1, j, &rLeft, &gLeft, &bLeft );
            BMP_GetPixelRGB( bmp, i+1, j, &rRight, &gRight, &bRight );
            BMP_GetPixelRGB( bmp, i, j-1, &rUp, &gUp, &bUp );
            BMP_GetPixelRGB( bmp, i, j+1, &rDown, &gDown, &bDown );
            if(r == 255 && g == 255 && b == 255)//dosli smo do bijelog pixela tj put
            {
                if( rLeft == 0 && gLeft == 0 && bLeft == 0) //ako je ljevo zid
                {
                    if(rRight == 255 && gRight == 255 && bRight == 255)//ako je desno put stavi zeleno
                        BMP_SetPixelRGB( bmp, i, j ,0, 255, 0);
                    else if(rRight == 0 && gRight == 0 && bRight == 0)//ako je desno zid
                    {
                        if((rDown==0 && gDown==0 && bDown==0)&& (rUp==255 && gUp==255 && bUp==255))//ako je dole zid i gore put stavi zeleno
                            BMP_SetPixelRGB( bmp, i, j ,0, 255, 0);
                        else if((rUp==0 && gUp==0 && bUp==0) && (rDown==255 && gDown==255 && bDown==255))//ako je gore zid a dole put stavi zeleno
                            BMP_SetPixelRGB( bmp, i, j ,0, 255, 0);
                    }
                }
                else if(rLeft == 255 && gLeft == 255 && bLeft == 255)//ako je ljevo put
                {
                    if(rRight == 0 && gRight == 0 && bRight == 0)//ako je desno zid stavi zeleno
                        BMP_SetPixelRGB( bmp, i, j ,0, 255, 0);
                    else if(rRight == 255 && gRight == 255 && bRight == 255)//ako je desno put
                    {
                        if(((rUp==255 && gUp==255 && bUp==255) || (rUp==0 && gUp==255 && bUp==0)) && (rDown==0 && gDown==0 && bDown==0)) // ako je gore put ili zeleno(cvor) i ako je dole zid stavi zeleno
                            BMP_SetPixelRGB( bmp, i, j ,0, 255, 0);
                        else if((rUp==0 && gUp==0 && bUp==0) && (rDown==255 && gDown==255 && bDown==255)) // ako je gore zid i ako je dole put stavi zeleno
                            BMP_SetPixelRGB( bmp, i, j ,0, 255, 0);
                        else if((rUp==255 && gUp==255 && bUp==255) && (rDown==255 && gDown==255 && bDown==255))//ako je gore put i dole put stavi zeleno
                            BMP_SetPixelRGB( bmp, i, j ,0, 255, 0);

                    }
                }
            }


        }
    }


    return 0;
}

Node generateGraphFromBMPAlgorithm(BMP* bmp, Node startNode, Node endNode)
{
    UINT    width, height;
    UCHAR   r, g, b;
    UINT    x, y;
    short int i = 1;//razlog je jer nije potrebno pregledavati prvi stupac jer je to zid a start imamo
    short int j = 1;//razlog je jer nije potrebno pregledavati prvi redak jer je zid a start imamo

    Node newNode=NULL;
    Pos Stack = createPos();

    startNode=generateNodeData(bmp,startNode);
    endNode=generateNodeData(bmp,endNode);

    Stack=PushList(Stack, startNode);
    Stack=PushList(Stack, endNode);

    width = BMP_GetWidth( bmp );
    height = BMP_GetHeight( bmp );
    width--;//razlog je jer nije potrebno pregledavati zadnji stupac jer je to zid a end imamo
    height--;//razlog je jer nije potrebno pregledavati zadnji redak jer je zid a end imamo

    printf("Width: %d Height: %d\n", width, height);

    for( j; j < height; j++)
    {
        i = 1;
        for( i; i < width; i++)
        {
            newNode=NULL;
            BMP_GetPixelRGB( bmp, i, j, &r, &g, &b );
            if( r == 0 && g == 255 && b == 0)//dosli smo do zelenog pixela tj noda
                newNode=createNode();

            if(newNode!=NULL)
            {
                newNode->x=i;
                newNode->y=j;
                newNode=generateNodeData(bmp,newNode);

                //PrintList(Stack);

                newNode=findAndConnectToNeighbours(bmp, Stack, newNode);
                if(newNode->numberOfMadeConnections < newNode->numberOfNeighbours)
                    Stack=PushList(Stack, newNode);
            }


        }
    }

    //PrintList(Stack);

    return startNode;
}

Node generateNodeData(BMP* bmp, Node node)
{
    UINT    width, height;
    UCHAR   r, g, b;
    short int i = 1;

    width = BMP_GetWidth( bmp );
    height = BMP_GetHeight( bmp );

    //provjera koliko ima mogucih puteva s cvora
    BMP_GetPixelRGB( bmp, node->x-1, node->y, &r, &g, &b );//prvo gledamo ljevo
    if(r == 255 && g == 255 && b == 255 || r == 0 && g == 255 && b == 0)
    {
         node->numberOfNeighbours++;
        //provjera koliko je udaljen ljevi susjed, ako je susjed zelene boje... uzmi distancu
        while( i <= node->x)
        {
            BMP_GetPixelRGB( bmp, node->x-i, node->y, &r, &g, &b );
            if(r == 0 && g == 255 && b == 0)
            {
                node->distanceToLeft=i;
                i=node->x;
            }
            else
                i++;
        }
    }
    i=1;
    BMP_GetPixelRGB( bmp, node->x+1, node->y, &r, &g, &b );//zatim desno
    if(r == 255 && g == 255 && b == 255 || r == 0 && g == 255 && b == 0)
    {
         node->numberOfNeighbours++;
        //provjera koliko je udaljen desni susjed, ako je susjed zelene boje... uzmi distancu
        while( i <= (width - node->x) )
        {
            BMP_GetPixelRGB( bmp, node->x+i, node->y, &r, &g, &b );
            if(r == 0 && g == 255 && b == 0)
            {
                node->distanceToRight=i;
                i=width;
            }
            else
                i++;
        }
    }
    i=1;
    BMP_GetPixelRGB( bmp, node->x, node->y-1, &r, &g, &b );//zatim gore
    if(r == 255 && g == 255 && b == 255 || r == 0 && g == 255 && b == 0)
    {
         node->numberOfNeighbours++;
        //provjera koliko je udaljen gornji susjed, ako je susjed zelene boje... uzmi distancu
        while( i <= node->y)
        {
            BMP_GetPixelRGB( bmp, node->x, node->y-i, &r, &g, &b );
            if(r == 0 && g == 255 && b == 0)
            {
                node->distanceToUp=i;
                i=node->y+1;
            }
            else
                i++;
        }
    }
    i=1;
    r=0;g=0;b=0;//resetiranje zbog finalnog noda, ostane vrijednost pixela povise jer pixela ispod nema
    BMP_GetPixelRGB( bmp, node->x, node->y+1, &r, &g, &b );//zatim dole
    if(r == 255 && g == 255 && b == 255 || r == 0 && g == 255 && b == 0)
    {
         node->numberOfNeighbours++;
        //provjera koliko je udaljen donji susjed, ako je susjed zelene boje... uzmi distancu
        while( i < (height-node->y) )
        {
            BMP_GetPixelRGB( bmp, node->x, node->y+i, &r, &g, &b );
            if(r == 0 && g == 255 && b == 0)
            {
                node->distanceToDown=i;
                i=height;
            }
            else
                i++;
        }
    }

    i=0;
    while( i < width)//nadi kordinate kraja tj odredista
    {
        BMP_GetPixelRGB( bmp, i, height - 1, &r, &g, &b );
        if( r == 0 && g == 0 && b == 0)
            i++;
        else if(r == 0 && g == 255 && b == 0)
            i=i + width;
    }

    i=i - width;

    //sada izracunat udaljenost cvora to kraja, pitagorin poucak
    node->distanceToEnd=sqrt( potency((height - 1- node->y), 2) + potency( abs( i - node->x ), 2) );

    return node;
}

Node findAndConnectToNeighbours(BMP* bmp, Pos list, Node node)
{
    Pos P = list->next;
    //spoji sa sa livin susjedom ako postoji
    if( node->distanceToLeft < 32767 )
    {
        while(P!=NULL)
        {
            if(P->node->distanceToRight == node->distanceToLeft && P->node->y == node->y && areTheyReallyRowNeighbours(bmp,P->node,node) && (node->x - P->node->x)==node->distanceToLeft)//provjera susjedstva
            {
                P->node->nextRight=node;
                node->nextLeft=P->node;

                P->node->numberOfMadeConnections++;
                node->numberOfMadeConnections++;

                if(P->node->numberOfNeighbours==P->node->numberOfMadeConnections)
                    removeNodeFromList( list , P->node );
                P=NULL;
            }
            else
                P=P->next;
        }
    }

    P = list->next;
    //spoji sa sa desnim susjedom ako postoji
    if( node->distanceToRight < 32767 )
    {
        while(P!=NULL)
        {
            if(P->node->distanceToLeft==node->distanceToRight && P->node->y==node->y && areTheyReallyRowNeighbours(bmp,node,P->node) && (P->node->x - node->x)==node->distanceToRight) //provjera susjedstva
            {
                P->node->nextLeft=node;
                node->nextRight=P->node;

                P->node->numberOfMadeConnections++;
                node->numberOfMadeConnections++;

                if(P->node->numberOfNeighbours==P->node->numberOfMadeConnections)
                    removeNodeFromList( list , P->node );

                P=NULL;
            }
            else
                P=P->next;
        }
    }

    P = list->next;
    //spoji sa sa gornjim susjedom ako postoji
    if( node->distanceToUp < 32767 )
    {
        while(P!=NULL)
        {
            if(P->node->distanceToDown == node->distanceToUp && P->node->x == node->x && areTheyReallyColumnNeighbours(bmp,P->node,node)&& (node->y - P->node->y)==node->distanceToUp)//provjera susjedstva
            {
                P->node->nextDown=node;
                node->nextUp=P->node;

                P->node->numberOfMadeConnections++;
                node->numberOfMadeConnections++;

                if(P->node->numberOfNeighbours==P->node->numberOfMadeConnections)
                    removeNodeFromList( list , P->node );

                P=NULL;
            }
            else
                P=P->next;
        }
    }

     P = list->next;
    //spoji sa sa donjim susjedom ako postoji
    if( node->distanceToDown < 32767 )
    {
        while(P!=NULL)
        {
            if(P->node->distanceToUp == node->distanceToDown && P->node->x == node->x && areTheyReallyColumnNeighbours(bmp,node,P->node) && (P->node->y - node->y)==node->distanceToDown)//provjera susjedstva
            {
                P->node->nextUp=node;
                node->nextDown=P->node;

                P->node->numberOfMadeConnections++;
                node->numberOfMadeConnections++;

                if(P->node->numberOfNeighbours==P->node->numberOfMadeConnections)
                    removeNodeFromList( list , P->node );

                P=NULL;
            }
            else
                P=P->next;
        }
    }

    return node;
}

bool areTheyReallyRowNeighbours(BMP* bmp, Node leftNode, Node rightNode)
{
    UCHAR   r, g, b;
    int i = leftNode->x;

    if(leftNode->y!=rightNode->y) return false;

    while( i < rightNode->x)
    {
        BMP_GetPixelRGB( bmp, i, leftNode->y , &r, &g, &b );
        if(r==0 && g==0 && b==0)
            return false;
        i++;
    }

    return true;
}

bool areTheyReallyColumnNeighbours(BMP* bmp,Node upperNode, Node lowerNode)
{
    UCHAR   r, g, b;
    int i = upperNode->y;

    if(upperNode->x!=lowerNode->x) return false;


    while( i <= lowerNode->y)
    {
        BMP_GetPixelRGB( bmp, upperNode->x, i , &r, &g, &b );
        if(r==0 && g==0 && b==0)
            return false;
        i++;
    }

    return true;
}

void removeNodeFromList( Pos list , Node node )
{
    Pos P=list;
    int isItDone=0;

    while(P->next!=NULL && isItDone==0)
    {
        if(node->x == P->next->node->x && node->y== P->next->node->y && node->numberOfMadeConnections==P->next->node->numberOfNeighbours)
        {
            P->next=P->next->next;
            isItDone=1;
        }

        else
            P=P->next;
    }
}


