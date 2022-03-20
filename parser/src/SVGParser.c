#include <stdio.h>
#include <string.h>
#include <math.h>
#include "SVGParser.h"
#include "LinkedListAPI.h"

/* The function is inspired from StructListDemo.c it basically frees the content of Attribute structhure*/
void deleteAttribute( void* data){

      Attribute* tmpName;

    if(data == NULL){
        return;
    }

    tmpName = (Attribute*)data;

    
        free(tmpName->name);
    
    

        free(tmpName);
    
    

}

/* The function is inspired from StructListDemo.c it basically convert to String the content of Attribute structhure*/
char* attributeToString(void* data){

    char * tmpStr;
    Attribute* tmpName;
    int len;

    if(data == NULL){
        return NULL;
    }

    tmpName = (Attribute*)data;

    len = strlen(tmpName -> name) + strlen(tmpName -> value) + 2; //Calculate te potenial length of your Attribute struct
    tmpStr = (char*)malloc(sizeof(char)*len);

    sprintf(tmpStr, "%s %s", tmpName->name, tmpName->value);

    return tmpStr;

}

int compareAttributes(const void *first, const void *second){

	Attribute* tmpName1;
	Attribute* tmpName2;

    if (first == NULL || second == NULL){
		return 0;
	}

	tmpName1 = (Attribute*)first;
	tmpName2 = (Attribute*)second;

    return strcmp((char*)tmpName1->name, (char*)tmpName2->name);

}


void deleteRectangle(void* data){

    Rectangle * tmpName;

    if (data == NULL){
		return;
	}

    tmpName = (Rectangle*)data;

    freeList(tmpName -> otherAttributes);
    free(tmpName);

}

char* rectangleToString(void* data){

    char* tmpStr;
	Rectangle* tmpName;
	int len;

	if (data == NULL){
		return NULL;
	}
    tmpName = (Rectangle*)data;
    char * otherAttr = toString(tmpName -> otherAttributes);
    

    len = 8+130 + strlen(otherAttr) ;
    tmpStr = (char*)malloc(sizeof(char)*len);

    sprintf(tmpStr, "%f %f %f %f %s %s \n", tmpName->x, tmpName->y, tmpName->width, tmpName -> height, tmpName -> units, otherAttr);

    free(otherAttr);
    return tmpStr;

}

int compareRectangles(const void *first, const void *second){

	Rectangle* tmpName1;
	Rectangle* tmpName2;

	if (first == NULL || second == NULL){
		return 0;
	}

	tmpName1 = (Rectangle*)first;
	tmpName2 = (Rectangle*)second;

    return strcmp((char *)tmpName1->units, (char*)tmpName2->units);


}


void deleteCircle(void* data){

    Circle* tmpName;
	if (data == NULL){
		return;
	}

    tmpName = (Circle*)data;

    freeList(tmpName -> otherAttributes);
    free(tmpName);

}


char* circleToString(void* data){

    if (data == NULL){
		return NULL;
	}

    

    Circle* tmpName = (Circle*)data;
    char * otherAttr = toString(tmpName -> otherAttributes);
    int len = 5+110 + strlen(otherAttr);
    char* tmpStr = (char*)malloc(sizeof(char)*len);



    sprintf(tmpStr, "%f %f %f %s %s", tmpName->cx, tmpName->cy, tmpName->r,tmpName -> units, otherAttr);

    free(otherAttr);
    return tmpStr;


}


int compareCircles(const void *first, const void *second){

	Circle* tmpName1;
	Circle* tmpName2;

	if (first == NULL || second == NULL){
		return 0;
	}

	tmpName1 = (Circle*)first;
	tmpName2 = (Circle*)second;

    return strcmp((char *)tmpName1->units, (char*)tmpName2->units);

}

void deletePath(void* data){

    Path* tmpName;

    if (data == NULL){
        return;
    }

    tmpName = (Path*)data;

    freeList(tmpName->otherAttributes);
    free(tmpName);

}

char* pathToString(void* data){

    char* tmpStr;
	Path* tmpName;
	int len;

    if (data == NULL){
		return NULL;
	}

    tmpName = (Path*)data;

    char * otherAttr = toString(tmpName -> otherAttributes);

    len = strlen(tmpName->data) + 3 + strlen(otherAttr);



    tmpStr = (char*)malloc(sizeof(char)*len);

    sprintf(tmpStr, "%s %s", tmpName->data, otherAttr);
    free(otherAttr);

 return tmpStr;

}

int comparePaths(const void *first, const void *second){


	Path* tmpName1;
	Path* tmpName2;

	if (first == NULL || second == NULL){
		return 0;
	}

	tmpName1 = (Path*)first;
	tmpName2 = (Path*)second;

    return strcmp((char *)tmpName1->data, (char*)tmpName2->data);

}

void deleteGroup(void* data){

	Group* tmpName;

	if (data == NULL){
		return;
	}

    tmpName = (Group*)data;

    freeList(tmpName-> otherAttributes);
    freeList(tmpName-> rectangles );
    freeList(tmpName -> paths);
    freeList(tmpName -> circles);
    freeList(tmpName -> groups);
    free(tmpName);

}

char* groupToString(void* data){

	char* tmpStr;
	Group* tmpName;


	if (data == NULL){
		return NULL;
	}

        tmpName = (Group*)data;

        tmpStr = (char*)malloc(20);


        sprintf(tmpStr, "[START]\n");

        char *listStr = NULL;

        if( getLength(tmpName -> otherAttributes) >0){
            
            listStr = toString(tmpName -> otherAttributes);
            tmpStr = realloc(tmpStr, strlen(listStr) + strlen(tmpStr) + 20);
            strcat(tmpStr, listStr);
            free(listStr);
        } 



        if( getLength(tmpName -> rectangles) >0){
            
            listStr = toString(tmpName -> rectangles);
            tmpStr = realloc(tmpStr, strlen(listStr) + strlen(tmpStr) + 20);
            strcat(tmpStr, listStr);
            free(listStr);
        }  

        if( getLength(tmpName -> circles) >0){
             
            listStr = toString(tmpName -> circles);
            tmpStr = realloc(tmpStr, strlen(listStr) + strlen(tmpStr) + 20);
            strcat(tmpStr, listStr);
             free(listStr);         
        }              

        if( getLength(tmpName -> paths) >0){
            
            listStr = toString(tmpName -> paths);
            tmpStr = realloc(tmpStr, strlen(listStr) + strlen(tmpStr) + 20);
            strcat(tmpStr, listStr);
            free(listStr);           
        }


        if( getLength(tmpName -> groups) >0){
            
            listStr = toString(tmpName -> groups);
            tmpStr = realloc(tmpStr, strlen(listStr) + strlen(tmpStr) + 20);
            strcat(tmpStr, listStr);
            free(listStr);           
        }

        tmpStr = realloc(tmpStr, sizeof(char)*strlen(tmpStr) + 20);
        strcat(tmpStr, "[THANKS]\n");


	return tmpStr;

}

int compareGroups(const void *first, const void *second){

return 0;



}


/*Helper function to deal with group inside a group, inspired from libXmlExample.c */
Group * populate_group_svg(xmlNode * a_node){



    Rectangle * rect;
    Circle * cir;
    Path * path;



    Group* group = malloc(sizeof(Group));
    group -> otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
    group -> rectangles = initializeList(&rectangleToString, &deleteRectangle, &compareRectangles);
    group -> circles = initializeList(&circleToString, &deleteCircle, &compareCircles);
    group -> paths = initializeList(&pathToString, &deletePath, &comparePaths);
    group -> groups = initializeList(&groupToString, &deleteGroup, &compareGroups);

    xmlNode *cur_node = NULL;
    xmlAttr *attr;

    for (attr = a_node-> parent ->properties; attr != NULL; attr = attr->next)
    {

            xmlNode *value = attr->children;
             if(attr != NULL){
                char *attrName = (char *)attr->name;
                int aNa = strlen(attrName) +2;

                char *cont = (char *)(value->content);
                int len = strlen(cont) + 2;

                Attribute * width = malloc(sizeof(Attribute) + len*sizeof(char));
                width -> name = malloc(aNa * sizeof(char));
                strcpy(width -> name, attrName);
                strcpy(width -> value, cont);

                insertBack(group -> otherAttributes, width);

             }
    }


    //Iterating through children of g tag

        for (cur_node = a_node ; cur_node != NULL; cur_node = cur_node->next)
        {

                if(strcmp((char *)cur_node -> name, "rect") == 0)
                {


                    rect = (Rectangle*)malloc(sizeof(Rectangle));
                    rect -> x = 0.0;
                    rect -> y = 0.0;
                    rect -> width = 0.0;
                    rect -> height = 0.0;
                    char * units = NULL;
                    rect -> otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
                        for (attr = cur_node->properties; attr != NULL; attr = attr->next)
                        {
                            xmlNode *value = attr->children;
                            if(strcmp((char *)attr -> name, "x") == 0){

                                
                                float cont = strtof((char*)value->content, &units);
                                rect -> x = cont;

                                if(units != NULL){
                                    strcpy(rect -> units, units);
                                }
                            }else  if(strcmp((char *)attr -> name, "y") == 0){

                               
                                float cont = strtof((char*)value->content, NULL);
                                rect -> y = cont;

                            

                            }else if(strcmp((char*)attr -> name, "width") == 0){

                                
                                float cont = strtof((char*)value->content, NULL);
                                rect -> width = cont;

                            

                            }else if(strcmp((char*)attr -> name, "height") == 0){

                             
                                float cont = strtof((char*)value->content, NULL);
                                rect -> height = cont;

                               

                            }else{


                                char *attrName = (char *)attr->name;
                                int aNa = strlen(attrName) +2;

                                char *cont = (char *)(value->content);
                                int len = strlen(cont) + 2;

                                Attribute * width = malloc(sizeof(Attribute) + len*sizeof(char));
                                width -> name = malloc(aNa * sizeof(char));
                                strcpy(width -> name, attrName);
                                strcpy(width -> value, cont);

                                insertBack(rect -> otherAttributes, width);
                            }

                        }

                 insertBack(group -> rectangles, (void*)rect);

                 }else if(strcmp((char*)cur_node -> name, "circle") == 0){

                    cir = (Circle*)malloc(sizeof(Circle));
                    cir -> cx = 0.0;
                    cir -> cy = 0.0;
                    cir -> r = 0.0;
                    char * units = NULL;
                    cir -> otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
                    for (attr = cur_node->properties; attr != NULL; attr = attr->next)
                    {
                        xmlNode *value = attr->children;
                        if(strcmp((char*)attr -> name, "cx") == 0){

                            
                            float cont = strtof((char*)value->content, &units);
                            cir -> cx = cont;

                            if(units != NULL){
                                strcpy(cir -> units, units);
                            }
                        }else if(strcmp((char*)attr -> name, "cy") == 0){

                           
                            float cont = strtof((char*)value->content, NULL);
                            cir -> cy = cont;

                            

                        }else if(strcmp((char*)attr -> name, "r") == 0){

                           
                            float cont = strtof((char*)value->content, NULL);
                            cir -> r = cont;

                           

                        }else{

                            char *attrName = (char *)attr->name;
                            int aNa = strlen(attrName) +2;

                            char *cont = (char *)(value->content);
                            int len = strlen(cont) + 2;

                            Attribute * width = malloc(sizeof(Attribute) + len*sizeof(char));
                            width -> name = malloc(aNa * sizeof(char));
                            strcpy(width -> name, attrName);
                            strcpy(width -> value, cont);

                            insertBack(cir -> otherAttributes, width);
                        }


                     }

                            insertBack(group -> circles, (void*)cir);
                 }else if(strcmp((char*)cur_node -> name, "path") == 0){


                    path = (Path*)malloc(sizeof(Path)+ 50000000*sizeof(char));

                    
                    path -> otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);

                        for (attr = cur_node->properties; attr != NULL; attr = attr->next)
                        {

                            xmlNode *value = attr->children;

                            if(strcmp((char*)attr -> name, "d") == 0){

                                char *cont = (char *)(value->content);
                                strcpy(path -> data, cont);

                            }else{


                                char *attrName = (char *)attr->name;
                                int aNa = strlen(attrName) +2;

                                char *cont = (char *)(value->content);
                                int len = strlen(cont) + 2;

                                Attribute * width = malloc(sizeof(Attribute) + len*sizeof(char));
                                width -> name = malloc(aNa * sizeof(char));
                                strcpy(width -> name, attrName);
                                strcpy(width -> value, cont);
                                insertBack(path -> otherAttributes, width);

                            }
                        }



                    insertBack(group -> paths, (void*)path);

                 }else if(strcmp((char*)cur_node -> name, "g") == 0){

                    Group * hold = populate_group_svg(cur_node->children);


                     insertBack(group -> groups, hold);

                 }

    }

    return group;
}



/* Helper function to populate the main svg struct , inspired from libXmlExample.c */
void populate_svg( xmlNode * a_node, SVG ** new){

    xmlNode *cur_node;
    SVG * hold = *new;


    Rectangle * rect;
    Path * path;

    Circle * cir;

for (cur_node = a_node; cur_node != NULL; cur_node = cur_node->next) {
    xmlAttr *attr;

    if(strcmp((char*)cur_node -> name, "svg") == 0){

        xmlNs *ns_node = cur_node -> ns;
        char *namespace = (char *)(ns_node -> href);
        strcpy(hold -> namespace, namespace);


        for (attr = cur_node->properties; attr != NULL; attr = attr->next)
        {
            xmlNode *value = attr->children;

             if(attr != NULL){
                char *attrName = (char *)attr->name;
                int aNa = strlen(attrName) +2;

                char *cont = (char *)(value->content);
                int len = strlen(cont) + 2;

                Attribute * width = malloc(sizeof(Attribute) + len*sizeof(char));
                width -> name = malloc(aNa * sizeof(char));
                strcpy(width -> name, attrName);
                strcpy(width -> value, cont);

                insertBack(hold -> otherAttributes, width);

            }

        }


    if(cur_node -> children != NULL){


        xmlNode * test_svg = NULL;

        for(test_svg = cur_node -> children ->next; test_svg != NULL; test_svg = test_svg -> next -> next){

            if(strcmp((char*)test_svg -> name, "title") == 0){

                char * title = (char*)xmlNodeGetContent(test_svg);
                if (title != NULL ){
                    strcpy(hold -> title, title);
                }

                free(title);
            }



            if(strcmp((char*)test_svg -> name, "desc") == 0){

                    char* desc = (char*)xmlNodeGetContent(test_svg);
                    if (desc != NULL ){
                    strcpy(hold -> description, desc);
                    }

                    free(desc);
            }



        }

    }

    }

    if(strcmp((char*)cur_node -> name, "rect") == 0){

        if(strcmp((char*)cur_node -> parent -> name, "g") !=0){


        rect = (Rectangle*)malloc(sizeof(Rectangle));
        rect -> x = 0.0;
        rect -> y = 0.0;
        rect -> width = 0.0;
        rect -> height = 0.0;
        char * units = NULL;
        rect -> otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
        for (attr = cur_node->properties; attr != NULL; attr = attr->next)
        {
                xmlNode *value = attr->children;
                 if(strcmp((char*)attr -> name, "x") == 0){
                    
                    float cont = strtof((char*)value->content, &units);
                    rect -> x = cont;

                    if(units != NULL){
                        strcpy(rect -> units, units);
                    }

                 }else  if(strcmp((char*)attr -> name, "y") == 0){

                    
                    float cont = strtof((char*)value->content, NULL);
                    rect -> y = cont;

                 

                 }else if(strcmp((char*)attr -> name, "width") == 0){

                    

                    float cont = strtof((char*)value->content, NULL);
                    rect -> width = cont;

            


                 }else if(strcmp((char*)attr -> name, "height") == 0){    

                    float cont = strtof((char*)value->content, NULL);
                    rect -> height = cont;

                }else{


                char *attrName = (char *)attr->name;
                int aNa = strlen(attrName) +2;

                char *cont = (char *)(value->content);
                int len = strlen(cont) + 2;

                Attribute * width = malloc(sizeof(Attribute) + len*sizeof(char));
                width -> name = malloc(aNa * sizeof(char));
                strcpy(width -> name, attrName);
                strcpy(width -> value, cont);

                insertBack(rect -> otherAttributes, width);


                }

        }

        insertBack(hold -> rectangles, (void*)rect);

    }
}



    if(strcmp((char*)cur_node -> name, "circle") == 0){
        if(strcmp((char*)cur_node -> parent -> name, "g") !=0){

        cir = (Circle*)malloc(sizeof(Circle));
        cir -> cx = 0.0;
        cir -> cy = 0.0;
        cir -> r = 0.0;
        char * units = NULL;
        cir -> otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
        for (attr = cur_node->properties; attr != NULL; attr = attr->next)
        {
            xmlNode *value = attr->children;
            if(strcmp((char*)attr -> name, "cx") == 0){

               
                float cont = strtof((char*)value->content, &units);
                cir -> cx = cont;

                if(units != NULL){
                    strcpy(cir -> units, units);
                }
            }else if(strcmp((char*)attr -> name, "cy") == 0){

              

                float cont = strtof((char*)value->content, NULL);
                cir -> cy = cont;

        

            }else if(strcmp((char*)attr -> name, "r") == 0){

               

                float cont = strtof((char*)value->content, NULL);
                cir -> r = cont;

              

            }else{

                char *attrName = (char *)attr->name;
                int aNa = strlen(attrName) +2;

                char *cont = (char *)(value->content);
                int len = strlen(cont) + 2;

                Attribute * width = malloc(sizeof(Attribute) + len*sizeof(char));
                width -> name = malloc(aNa * sizeof(char));
                strcpy(width -> name, attrName);
                strcpy(width -> value, cont);

                insertBack(cir -> otherAttributes, width);


            }


        }

        insertBack(hold -> circles, (void*)cir);
    }
    }



    if(strcmp((char*)cur_node -> name, "path") == 0){
        if(strcmp((char*)cur_node -> parent -> name, "g") !=0){


    path = (Path*)malloc(sizeof(Path) + 50000000*sizeof(char));
   
    path -> otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);

    for (attr = cur_node->properties; attr != NULL; attr = attr->next)
    {

        xmlNode *value = attr->children;

        if(strcmp((char*)attr -> name, "d") == 0){

            
            char *cont = (char *)(value->content);
            strcpy(path -> data, cont);

        }else{


                char *attrName = (char *)attr->name;
                int aNa = strlen(attrName) +2;

                char *cont = (char *)(value->content);
                int len = strlen(cont) + 2;

                Attribute * width = malloc(sizeof(Attribute) + len*sizeof(char));
                width -> name = malloc(aNa * sizeof(char));
                strcpy(width -> name, attrName);
                strcpy(width -> value, cont);
                insertBack(path -> otherAttributes, width);

        }

    }

    insertBack(hold -> paths, (void*)path);

    }
    }


    if(strcmp((char*)cur_node -> name, "g") == 0){
        if(strcmp((char*)cur_node -> parent -> name, "g") !=0){

            xmlNode * hola = cur_node -> children;
            Group * group = populate_group_svg(hola);
            insertBack(hold -> groups, (void*)group);

      

         }
    }

    populate_svg(cur_node -> children, &hold);

    }

*new = hold;

}

//helper function to get group inside group using recursion

void checkGroup(List * list, Group * helper){

    ListIterator iter_group = createIterator(helper -> groups);
    void* group;
    while ((group = nextElement(&iter_group)) != NULL){

        checkGroup(list, group);
        insertBack(list,group);

    }


}

/* Helper function to delete the List without erasing the content inside list this function also free the list pointer passed as parameter */
void dummyDelete(List * img){

    if(img == NULL){
        return;
    }

    if(img -> head == NULL && img -> tail == NULL){
        free(img);
        return;
    }

    Node * hold1;
    Node * hold2;
    
    while( img -> head != NULL){
        hold1 = img -> head;
        hold2 = hold1;
        img -> head = img -> head -> next;
        free(hold2);
    }


    free(img);

}

/* Mandatory function inspired from StructListDemo.c this function basically itterate the list store inside svg struct and Group struct and make one big list out of it  */
List* getRects(const SVG* img){

    if(img == NULL){
        return NULL;
    }else{

        List * rect = initializeList(&rectangleToString, &deleteRectangle, &compareRectangles);
        Rectangle * dumRec = NULL;
        void* rect_normal;

        //Create an iterator - again, the iterator is allocated on the stack
        ListIterator iter_rect;

        iter_rect = createIterator(img -> rectangles);

        while ((rect_normal = nextElement(&iter_rect)) != NULL){
            Rectangle* tmpRect = (Rectangle*)rect_normal;

            dumRec = tmpRect;

            insertBack(rect,(void *)dumRec);

        }


        List * groups = getGroups(img);


        for(Node* rec = groups -> head; rec!= NULL; rec= rec->next){

            if(((Group*)(rec -> data)) -> rectangles->length > 0){

                for(Node * rectan = ((Group*)(rec -> data)) -> rectangles->head; rectan != NULL; rectan = rectan -> next){

                    insertBack(rect, rectan->data);
                }


            }

        }
        dummyDelete(groups);
        return rect;
    }

}

/* Mandatory function inspired from StructListDemo.c this function basically itterate the list store inside svg struct and Group struct and make one big list out of it  */
List* getCircles(const SVG* img){

    if(img == NULL){
        return NULL;
    }else{

        List * cir = initializeList(&circleToString, &deleteCircle, &compareCircles);
        Circle * dumCir = NULL;
        void* cir_normal;

        //Create an iterator - again, the iterator is allocated on the stack
        ListIterator iter_cir = createIterator(img -> circles);

        while ((cir_normal = nextElement(&iter_cir)) != NULL){
            Circle* tmpCir = (Circle*)cir_normal;

            dumCir = tmpCir;

            insertBack(cir,dumCir);

        }


        List * groups = getGroups(img);


        for(Node* cirNo = groups -> head; cirNo!= NULL; cirNo= cirNo->next){

            if(((Group*)(cirNo -> data)) -> circles->length >0){

                for(Node * circ = ((Group*)(cirNo -> data)) -> circles->head; circ != NULL; circ = circ -> next){

                    insertBack(cir, circ->data);
                }


            }

        }

        dummyDelete(groups);
        return cir;
    }

}

/* Mandatory function inspired from StructListDemo.c this function basically itterate the list store inside svg struct and Group struct and make one big list out of it  */
List* getPaths(const SVG* img){

    if(img == NULL){
        return NULL;
    }else{

        List * pat = initializeList(&pathToString, &deletePath, &comparePaths);
        Path * dumPat = NULL;
        void* pat_normal;

        //Create an iterator - again, the iterator is allocated on the stack
        ListIterator iter_pat = createIterator(img -> paths);

        while ((pat_normal = nextElement(&iter_pat)) != NULL){
            Path* tmpPat = (Path*)pat_normal;

            dumPat = tmpPat;

            insertBack(pat,dumPat);

        }

        List * groups = getGroups(img);

        for(Node* patNo = groups -> head; patNo != NULL; patNo= patNo->next){

            if(((Group*)(patNo -> data)) -> paths->length >0){

                for(Node * pathInside = ((Group*)(patNo -> data)) -> paths->head; pathInside != NULL; pathInside = pathInside -> next){

                    insertBack(pat, pathInside->data);
                }


            }

        }
        dummyDelete(groups);
        return pat;
    }

}

/* Mandatory function inspired from StructListDemo.c this function basically itterate the list store inside svg struct and Group struct and make one big list out of it  */
List* getGroups(const SVG* img){

    if(img == NULL){
        return NULL;
    }else{

        List * group = initializeList(&groupToString, &deleteGroup, &compareGroups);
        Group * group_normal = NULL;


        ListIterator iter_group = createIterator(img -> groups);

        while ((group_normal = nextElement(&iter_group)) != NULL){

            checkGroup(group, group_normal);

            insertBack(group,group_normal);

        }

        return group;
    }
}



/* This function basically calls one of the get function itterate through the link list and check for area by comparing to area parameter passes by the user and if matched increment the counter*/
int numRectsWithArea(const SVG* img, float area){

    if(img == NULL){
        return 0;
    }else{

        
        void* rect_normal;
        int countRect =0;
        //Create an iterator - again, the iterator is allocated on the stack

        List * rect_stuff = getRects(img);
        ListIterator iter_rect = createIterator(rect_stuff);

        while ((rect_normal = nextElement(&iter_rect)) != NULL){
            Rectangle* tmpRect = (Rectangle*)rect_normal;

            if(ceil(tmpRect -> width * tmpRect -> height) == ceil(area)){
                countRect = countRect +1;
            }

        }
        dummyDelete(rect_stuff);
 
        return countRect;
    }

}

/* This function basically calls one of the get function itterate through the link list and check for area by comparing to area parameter passes by the user and if matched increment the counter*/
int numCirclesWithArea(const SVG* img, float area){

    if(img == NULL){
        return 0;
    }else{


        void* cir_normal;
        int countCir =0;
        //Create an iterator - again, the iterator is allocated on the stack

        List * Cir_stuff = getCircles(img);
        ListIterator iter_cir = createIterator(Cir_stuff);

        while ((cir_normal = nextElement(&iter_cir)) != NULL){
            Circle* tmpCir = (Circle*)cir_normal;

            if(ceil(tmpCir -> r * tmpCir -> r * 3.14159265) == ceil(area)){
                countCir = countCir +1;
            }

        }
        dummyDelete(Cir_stuff);

        return countCir;
    }

}


/* This basically checks for the same string passed by the user inside the path List if matched increment the counter*/
int numPathsWithdata(const SVG* img, const char* data){

    if(img == NULL){
        return 0;
    }else{

       
        void* pat_normal;
        int countPat =0;
        //Create an iterator - again, the iterator is allocated on the stack

        List * Path_stuff = getPaths(img);
        ListIterator iter_pat = createIterator(Path_stuff);

        while ((pat_normal = nextElement(&iter_pat)) != NULL){
            Path* tmpPat = (Path*)pat_normal;

            if(strcmp(tmpPat -> data, data) == 0){
                countPat = countPat +1;
            }

        }
        dummyDelete(Path_stuff);
 
        return countPat;
    }


}

int numGroupsWithLen(const SVG* img, int len){

    if(img == NULL){
        return 0;
    }else{

        
        void * group_normal;
        int countGroup =0;
       
        //Create an iterator - again, the iterator is allocated on the stack

        List * Group_stuff = getGroups(img);
        ListIterator iter_group = createIterator(Group_stuff);

        while ((group_normal = nextElement(&iter_group)) != NULL){
            Group* tmpGroup = (Group*)group_normal;

            if((getLength( tmpGroup -> rectangles) + getLength( tmpGroup -> circles) +getLength( tmpGroup -> paths)+getLength( tmpGroup -> groups)) == len){
                countGroup = countGroup +1;
            }


        }
        dummyDelete(Group_stuff);
 
        return countGroup;
    }


}

/* This function simple calculates total number of attribute inside every list in svg struct and dummy free the list genrated using geter functions, this is inspired from StructListDemo.c*/
int numAttr(const SVG* img){

        if(img == NULL){
            return 0;
        }else{


        int len = 0;

        len = len + getLength(img -> otherAttributes);

            List * rect_stuff = getRects(img);
            if(rect_stuff != NULL){
                void* rect_normal;
                ListIterator iter_rect = createIterator(rect_stuff);
                while ((rect_normal = nextElement(&iter_rect)) != NULL){
                    Rectangle* tmpRect = (Rectangle*)rect_normal;

                    len =  len + getLength(tmpRect -> otherAttributes);

                }
                dummyDelete(rect_stuff);

            }

            List * Cir_stuff = getCircles(img);
            if(Cir_stuff != NULL){
                void* cir_normal;
                ListIterator iter_cir = createIterator(Cir_stuff);
                while ((cir_normal = nextElement(&iter_cir)) != NULL){
                    Circle* tmpCir = (Circle*)cir_normal;

                    len = len + getLength(tmpCir -> otherAttributes);

                }
                dummyDelete(Cir_stuff);
            }

            
            List * Path_stuff = getPaths(img);
            if(Path_stuff != NULL){
                void* pat_normal;

                ListIterator iter_pat = createIterator(Path_stuff);

                while ((pat_normal = nextElement(&iter_pat)) != NULL){
                    Path* tmpPat = (Path*)pat_normal;

                    len = len + getLength(tmpPat -> otherAttributes);

                }
                dummyDelete(Path_stuff);
            }

            List * Group_stuff = getGroups(img);
            if(Group_stuff != NULL){
                void * group_normal;
                ListIterator iter_group = createIterator(Group_stuff);

                while ((group_normal = nextElement(&iter_group)) != NULL){
                    Group* tmpGroup = (Group*)group_normal;

                    len = len + getLength(tmpGroup -> otherAttributes);

                }
                dummyDelete(Group_stuff);
            }  

            return len;

    }

}

/* This is a mandatory function which basically parse the svg file and populate the svg struct using call to helper function and returns a pointer to the SVG struct, it is inspired from libXmlExample.c*/

SVG* createSVG(const char* fileName){

    xmlDoc *doc = NULL;
    xmlNode * a_node = NULL;

    if(fileName == NULL){
        return NULL;
    }



    LIBXML_TEST_VERSION

    
    doc = xmlReadFile(fileName, NULL, 0);

    if (doc == NULL) {
        printf("error: could not parse file %s\n", fileName);
        return NULL;
    }

    
    a_node = xmlDocGetRootElement(doc);

    SVG * hold = malloc(sizeof(SVG));



    hold -> otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
    hold -> rectangles = initializeList(&rectangleToString, &deleteRectangle, &compareRectangles);
    hold -> circles = initializeList(&circleToString, &deleteCircle, &compareCircles);
    hold -> paths = initializeList(&pathToString, &deletePath, &comparePaths);
    hold -> groups = initializeList(&groupToString, &deleteGroup, &compareGroups);
    strcpy(hold -> namespace, "");
    strcpy(hold -> title, "");
    strcpy(hold -> description, "");


    
    populate_svg(a_node, &hold);

   

    xmlFreeDoc(doc);

    xmlCleanupParser();

    return hold;
}


void deleteSVG(SVG* img){

    if(img != NULL){

        freeList(img-> otherAttributes);
        freeList(img-> rectangles);
        freeList(img -> paths);
        freeList(img -> circles);
        freeList(img -> groups);
        free(img);

    }
}


/* This function basically print all the content inside SVG struct */
char* SVGToString(const SVG* img){

        if(img == NULL){
            return "";
        }else{


        char *tmpStr = malloc(strlen(img -> namespace) + strlen(img -> title) + strlen(img -> description) + 50);

        sprintf(tmpStr, "[NameSpace] %s\n[Tittle] %s\n[Description] %s\n", img->namespace, img -> title, img -> description);

        char *listStr = NULL;

        if( getLength(img -> otherAttributes) >0){
            
            listStr = toString(img -> otherAttributes);

            tmpStr = realloc(tmpStr, strlen(listStr) + strlen(tmpStr) + 20);


            
            strcat(tmpStr, "[OtherAttri]");
            strcat(tmpStr, listStr);
            strcat(tmpStr, "\n");
            free(listStr);

        } 


        if( getLength(img -> rectangles) >0){
            
            listStr = toString(img -> rectangles);
            tmpStr = realloc(tmpStr, strlen(listStr) + strlen(tmpStr) + 20);
            strcat(tmpStr, "[Rect]");
            
            strcat(tmpStr, listStr);
            strcat(tmpStr, "\n");
            free(listStr);

        }

        if( getLength(img -> circles) >0){
             
            listStr = toString(img -> circles);
            tmpStr = realloc(tmpStr, strlen(listStr) + strlen(tmpStr) + 20);

            strcat(tmpStr, "[Circles]");
            
            strcat(tmpStr, listStr);
            strcat(tmpStr, "\n");
            free(listStr);         
        }

        if( getLength(img -> paths) >0){
            
            listStr = toString(img -> paths);
            tmpStr = realloc(tmpStr, strlen(listStr) + strlen(tmpStr) + 20);
            strcat(tmpStr, "[Paths]");
            strcat(tmpStr, listStr);
            strcat(tmpStr, "\n");
            free(listStr);           
        }


        if( getLength(img -> groups)  >0){
           
            listStr = toString(img -> groups);
            tmpStr = realloc(tmpStr, strlen(listStr) + strlen(tmpStr) + 20);
            strcat(tmpStr, "[Groups]");
            strcat(tmpStr, listStr);
            strcat(tmpStr, "\n");
            free(listStr);            
        }

        return tmpStr;

    }

}





/******************************** A2 stuff ******************************************************/
/*Helper function*/

int xmlValidate(xmlDoc * temp, const char* schemaFile){

    xmlDoc * doc = temp;

    xmlSchema *schema = NULL;

    if(doc == NULL){
        return -1;
    }

    xmlLineNumbersDefault(1);

    xmlSchemaParserCtxt *ctxt = xmlSchemaNewParserCtxt(schemaFile);

    if(ctxt == NULL){

        xmlFreeDoc(doc);
        xmlCleanupParser();

        return -1;
    }

    xmlSchemaSetParserErrors(ctxt, (xmlSchemaValidityErrorFunc) fprintf, (xmlSchemaValidityWarningFunc) fprintf, stderr);
    schema = xmlSchemaParse(ctxt);

    if(schema == NULL){

        xmlSchemaFreeParserCtxt(ctxt);

        xmlFreeDoc(doc);
        xmlCleanupParser();

        return -1;        

    }

    xmlSchemaValidCtxt *temp_ctxt;
   

    temp_ctxt = xmlSchemaNewValidCtxt(schema);

    if(temp_ctxt == NULL){

        xmlSchemaFreeParserCtxt(ctxt);
        xmlSchemaFree(schema);

        xmlFreeDoc(doc);
        xmlCleanupParser();

        return -1;  
    }

    xmlSchemaSetValidErrors(temp_ctxt, (xmlSchemaValidityErrorFunc) fprintf, (xmlSchemaValidityWarningFunc) fprintf, stderr);

    int hold = xmlSchemaValidateDoc(temp_ctxt, doc);

    xmlSchemaFreeParserCtxt(ctxt);
    xmlSchemaFree(schema);
    xmlSchemaFreeValidCtxt(temp_ctxt);
    xmlFreeDoc(doc);
    xmlSchemaCleanupTypes();
    xmlCleanupParser();
  //  xmlMemoryDump();

    return hold;

}

SVG* createValidSVG(const char* fileName, const char* schemaFile){


    if(fileName == NULL || schemaFile == NULL){
        return NULL;
    }

    xmlDoc *doc = xmlReadFile(fileName, NULL, 0);
    

    if(doc == NULL){
        xmlCleanupParser();
        return NULL;
    }

    int ret = xmlValidate(doc, schemaFile);

    if(ret == 0){
        SVG * temp = createSVG(fileName);
 
        if(temp == NULL){
            return NULL;
        }

        return temp;
    }else{
        return NULL;
    }

    return NULL;

/*
    
    xmlNode * a_node = NULL;



    LIBXML_TEST_VERSION;

    
    
    char *XMLFileName = fileName;



    
    

    doc = 
    a_node = xmlDocGetRootElement(doc);


    if (doc == NULL)
    {
        fprintf(stderr, "Could not parse %s\n", XMLFileName);
    } else {


        ret = 

        if (ret == 0)
        {
            printf("%s validates\n", XMLFileName);

            SVG * hold = malloc(sizeof(SVG));

            hold -> otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
            hold -> rectangles = initializeList(&rectangleToString, &deleteRectangle, &compareRectangles);
            hold -> circles = initializeList(&circleToString, &deleteCircle, &compareCircles);
            hold -> paths = initializeList(&pathToString, &deletePath, &comparePaths);
            hold -> groups = initializeList(&groupToString, &deleteGroup, &compareGroups);
            strcpy(hold -> namespace, "");
            strcpy(hold -> title, "");
            strcpy(hold -> description, "");


            
            populate_svg(a_node, &hold);

        

            xmlFreeDoc(doc);

            xmlCleanupParser();


        }
        else if (ret > 0)
        {
            printf("%s fails to validate\n", XMLFileName);
            return NULL
        }
        else
        {
            printf("%s validation generated an internal error\n", XMLFileName);
            return NULL;
        }

        xmlSchemaFreeValidCtxt(ctxt);
        

    }

    // free the resource
    if(schema != NULL)
    

    xmlSchemaCleanupTypes();


    return NULL;
*/
}



void attrToXMLTree(xmlNode * root_node, List* demo){

        void* attr_normal;
        ListIterator attr_rect;

        attr_rect = createIterator(demo);

            while ((attr_normal = nextElement(&attr_rect)) != NULL){
            
            Attribute* tmpAttr = (Attribute*)attr_normal;

            xmlNewProp(root_node, (xmlChar *)  tmpAttr -> name , (xmlChar *) tmpAttr -> value);
            
            }
}

void rectToXMLTree(xmlNode * root_node, List* demo){

        void* rect_normal;
        ListIterator iter_rect;
        xmlNode * node = NULL;
        Rectangle* tmpRect = NULL;
        char hold[256]; 

        iter_rect = createIterator(demo);

            while ((rect_normal = nextElement(&iter_rect)) != NULL){

                tmpRect = (Rectangle*)rect_normal;

                node = xmlNewChild(root_node, NULL, (xmlChar *)  "rect", NULL);

                
                sprintf(hold, "%f%s", tmpRect->x, tmpRect->units);
                xmlNewProp(node, (xmlChar *)  "x", (xmlChar *) hold);

                sprintf(hold, "%f%s", tmpRect->y, tmpRect->units);
                xmlNewProp(node, (xmlChar *)  "y", (xmlChar *)  hold);

                sprintf(hold, "%f%s", tmpRect->width, tmpRect->units);
                xmlNewProp(node, (xmlChar *)  "width", (xmlChar *)  hold);

                sprintf(hold, "%f%s", tmpRect->height, tmpRect->units);
                xmlNewProp(node, (xmlChar *)  "height", (xmlChar *)  hold);

                if(getLength(tmpRect -> otherAttributes) >0){
                    attrToXMLTree(node, tmpRect -> otherAttributes);
                }



            }

}

void cirToXMLTree(xmlNode * root_node, List* demo){

        void* cir_normal;

        //Create an iterator - again, the iterator is allocated on the stack
        ListIterator iter_cir = createIterator(demo);
        Circle* tmpCir = NULL;
        xmlNode * node = NULL;
        char hold[256]; 

        while ((cir_normal = nextElement(&iter_cir)) != NULL){
            tmpCir = (Circle*)cir_normal;
            node = xmlNewChild(root_node, NULL, (xmlChar *)  "circle", NULL);

            sprintf(hold, "%f%s", tmpCir->cx, tmpCir->units);
            xmlNewProp(node, (xmlChar *)  "cx", (xmlChar *) hold);

            sprintf(hold, "%f%s", tmpCir->cy, tmpCir->units);
            xmlNewProp(node, (xmlChar *)  "cy", (xmlChar *) hold);

            sprintf(hold, "%f%s", tmpCir->r, tmpCir->units);
            xmlNewProp(node, (xmlChar *)  "r", (xmlChar *) hold);

            if(getLength(tmpCir -> otherAttributes) > 0){
                attrToXMLTree(node, tmpCir -> otherAttributes);
            }
                
        }

}

void pathToXMLTree(xmlNode * root_node, List* demo){
        void* pat_normal;

        //Create an iterator - again, the iterator is allocated on the stack
        ListIterator iter_pat = createIterator(demo);
        Path* tmpPat = NULL;
        xmlNode * node = NULL;

        while ((pat_normal = nextElement(&iter_pat)) != NULL){

            tmpPat = (Path*)pat_normal;
            node = xmlNewChild(root_node, NULL, (xmlChar *)  "path", NULL);

            xmlNewProp(node, (xmlChar *)  "d", (xmlChar *) tmpPat -> data);

            if(getLength(tmpPat -> otherAttributes) > 0){
                attrToXMLTree(node, tmpPat -> otherAttributes);
            }


        }

}


void groupToXMLTree(xmlNode * root_node, List* demo){


        Group * group_normal = NULL;

        ListIterator iter_group = createIterator(demo);

        xmlNode * node = NULL;

        while ((group_normal = nextElement(&iter_group)) != NULL){

            node = xmlNewChild(root_node, NULL, (xmlChar *)  "g", NULL);

            if(getLength(group_normal -> otherAttributes) > 0){
                attrToXMLTree(node, group_normal -> otherAttributes);
            }

            if(getLength(group_normal -> rectangles) >0){
                rectToXMLTree(node, group_normal -> rectangles);
            }

            if(getLength(group_normal -> circles) > 0){
                cirToXMLTree(node, group_normal -> circles);
            }

            if(getLength(group_normal -> paths) > 0){
                pathToXMLTree(node , group_normal -> paths);
            }

            if(getLength(group_normal -> groups) > 0){
                groupToXMLTree(node, group_normal -> groups);
            }

        }


}



xmlDoc * structToXMLTree(const SVG* img){

        if(img == NULL){
            return NULL;
        }
        xmlDoc* doc = NULL;
        xmlNode* root_node = NULL;

        doc = xmlNewDoc(BAD_CAST "1.0");
        root_node = xmlNewNode(NULL, BAD_CAST "svg");
        xmlDocSetRootElement(doc, root_node);
        
        xmlNs *nameSpace = xmlNewNs(root_node, (xmlChar *) img -> namespace, NULL);
        xmlSetNs(root_node, nameSpace);

        


        //add functinoality for namespace, otherAttr of SVG, title, desc

        if(strlen(img -> title) > 0){
        
        xmlNewChild(root_node, NULL, (xmlChar *)"title", (xmlChar *)img -> title);

        }

        if(strlen(img -> description) > 0){
            
             xmlNewChild(root_node, NULL, (xmlChar *)"desc", (xmlChar *)img -> description);
            
        }        

        if(getLength(img -> otherAttributes) > 0){
            attrToXMLTree(root_node, img -> otherAttributes);
        }

        if(getLength(img -> rectangles) > 0){

            rectToXMLTree(root_node, img -> rectangles);

        }

        if(getLength(img -> circles) > 0){

            cirToXMLTree(root_node, img -> circles);
        }

        if(getLength(img -> paths) > 0){
            pathToXMLTree(root_node , img -> paths);
        }

        if(getLength(img -> groups) > 0){
            groupToXMLTree(root_node, img -> groups);
        }

        return doc;

}



int checkAttr(List * list){
        if(list == NULL){
            return 0;
        }

        Attribute * attri = NULL;
        ListIterator iter_attri = createIterator(list);
        

        while ((attri = nextElement(&iter_attri)) != NULL){

            if(attri -> value == NULL){
                return 0;
            }

            if(attri -> name == NULL){
                return 0;
            }

        }


    return 1;

}



/*
This function check if all the value here is not null 

*/
int checkRect(List * list){

        if(list == NULL){
            return 0;
        }
        Rectangle* rect_normal = NULL;
        int hold = 1;
        //Create an iterator - again, the iterator is allocated on the stack

        
        ListIterator iter_rect = createIterator(list);

        while ((rect_normal = nextElement(&iter_rect)) != NULL){

            if(checkAttr(rect_normal -> otherAttributes) == 0){

                hold = 0;

            }

            if(rect_normal -> units == NULL){

                hold = 0;

            }

            if(rect_normal -> height < 0){
                hold = 0;
            }

            if(rect_normal -> width < 0){
                hold = 0;
            }

            if(rect_normal -> otherAttributes == NULL){
                hold = 0;
            }

        }

        
        return hold;

    }

int checkCircle(List * list){

        if(list == NULL){
            return 0;
        }

        Circle* cir_normal = NULL;
        int hold = 1;
        //Create an iterator - again, the iterator is allocated on the stack

        
        ListIterator iter_cir = createIterator(list);

        while ((cir_normal = nextElement(&iter_cir)) != NULL){

            if(cir_normal -> otherAttributes == NULL){
                hold = 0;
            }else if(checkAttr(cir_normal -> otherAttributes) == 0){

                hold = 0;

            }else if(cir_normal -> units == NULL){

                hold = 0;

            }else if(cir_normal -> r < 0){
                hold = 0;
            }


        }

        
        return hold;


}

int checkPath(List * list){

        if(list == NULL){
            return 0;
        }

        Path* path_normal = NULL;
        int hold = 1;
        //Create an iterator - again, the iterator is allocated on the stack

       
        ListIterator iter_path = createIterator(list);

        while ((path_normal = nextElement(&iter_path)) != NULL){

            if(path_normal -> otherAttributes == NULL){
                hold = 0;
            }else if(checkAttr(path_normal -> otherAttributes) == 0){

                hold = 0;

            }else if(path_normal -> data == NULL){

                hold = 0;

            }

        }
        return hold;
}

int validateGroup(List * list){

        if(list == NULL){
            return 0;
        }

        Group* group_normal = NULL;
        int hold = 1;
        //Create an iterator - again, the iterator is allocated on the stack

        
        ListIterator iter_group = createIterator(list);

        while ((group_normal = nextElement(&iter_group)) != NULL){

            if(checkRect(group_normal -> rectangles) == 0){

                hold = 0;

            }else if(checkCircle(group_normal -> circles) == 0){

                hold = 0;

            }else if(checkPath(group_normal -> paths) == 0){
                
                hold = 0;
            
            }else if(validateGroup(group_normal -> groups) == 0){
            
                hold = 0;
            
            }else if(checkAttr(group_normal -> otherAttributes) == 0){
                hold = 0;
            }


        }

        return hold;

}


/** Function to validating an existing an SVG struct against a SVG schema file
 *@pre 
    SVG struct exists and is not NULL
    schema file name is not NULL/empty, and represents a valid schema file
 *@post SVG has not been modified in any way
 *@return the boolean aud indicating whether the SVG is valid
 *@param obj - a pointer to a SVGdoc struct
 *@param obj - the name iof a schema file
**/
bool validateSVG(const SVG* img, const char* schemaFile){


    if(img == NULL){
        return false;
    }

    if(schemaFile == NULL){
        return false;
    }


    if(checkRect(img -> rectangles) == 0 || checkCircle(img -> circles) == 0 || checkPath(img -> paths) == 0 || validateGroup(img -> groups) == 0 || checkAttr(img -> otherAttributes) == 0){
        return false;
    }

    xmlDoc *doc = structToXMLTree(img);

    int temp = xmlValidate(doc, schemaFile); 
    
    
    if(temp == 0){
        return true;
    }else{
        return false;
    }

}


bool updateOther(List * list, Attribute * newAttribute){

    if(list == NULL || newAttribute == NULL){
        return false;
    }

    if(newAttribute -> name == NULL || newAttribute -> value == NULL){
        return false;
    }

    ListIterator iter = createIterator(list);

    Attribute * attri = NULL;
    bool hold = false;

    if(getLength(list) > 0){

        while ((attri = nextElement(&iter)) != NULL){

            if(strcmp(newAttribute -> name, attri -> name) == 0){
         
                hold = true;
                strcpy(attri -> value, newAttribute -> value);
                deleteAttribute(newAttribute);
                return true;
                
            }


        }        


    }

    if(!hold){
        //free(attri -> value);
        //attri -> value = (char *)malloc(sizeof()  + strlen(newAttribute -> value) + 1 *sizeof(char));
        //strcpy(attri -> value, newAttribute -> value);
        //return true;
        insertBack(list, newAttribute);
        
        return true;
    }

    deleteAttribute(newAttribute);
    return false;

}



/** Function to setting an attribute in an SVG or component
 *@pre
    SVG object exists, is valid, and and is not NULL.
    newAttribute is not NULL
 *@post The appropriate attribute was set corectly
 *@return a boolean value indicating success or failure of the function
 *@param
    struct - a pointer to an SVG struct
    elemType - enum value indicating elemtn to modify
    elemIndex - index of thje lement to modify
    newAttribute - struct containing name and value of the updated attribute
 **/
bool setAttribute(SVG* img, elementType elemType, int elemIndex, Attribute* newAttribute){

    if(img == NULL){
        return false;
    }else if(elemType != CIRC && elemType != RECT && elemType != PATH && elemType != SVG_IMG && elemType != GROUP){
        return false;
    }else if(newAttribute == NULL){
        return false;
    }

    if(newAttribute -> name == NULL){
        
        return false;
    }else if(newAttribute -> value == NULL){
        
        return false;
    }

    if(!(checkAttr(img -> otherAttributes) && checkCircle(img -> circles) && checkPath(img -> paths) && checkRect(img -> rectangles) && validateGroup(img -> groups))){
        deleteAttribute(newAttribute);
        return false;
    }

   if(elemType == SVG_IMG){

       ListIterator iter = createIterator(img -> otherAttributes);
       Attribute *attr = NULL;
        bool hold = false;
    if(getLength(img -> otherAttributes) > 0){

        while ((attr = nextElement(&iter)) != NULL){

            if(strcmp(attr -> name, newAttribute -> name) == 0){
                hold = true;
                strcpy(attr -> value, newAttribute -> value);
                deleteAttribute(newAttribute);
                return true;
            }

        }
    } 
   if(!hold){
       
        insertBack(img -> otherAttributes, newAttribute);
        
        return true;
    }else{
       deleteAttribute(newAttribute);
        return false;
    }

    
    

   }else if(elemType == CIRC){

       int index = 0;
       ListIterator iter_cir = createIterator(img -> circles);
       Circle *cir = NULL;
       bool hold = false;

        while ((cir = nextElement(&iter_cir)) != NULL){
        
            if(index == elemIndex){

                if(strcmp(newAttribute -> name, "cx") == 0){
                    cir -> cx = strtof(newAttribute -> value, NULL);
                    deleteAttribute(newAttribute);
                    return true;
                }else if(strcmp(newAttribute -> name, "cy") == 0){
                    cir -> cy =  strtof(newAttribute -> value, NULL);
                    deleteAttribute(newAttribute);
                    return true;
                }else if(strcmp(newAttribute -> name, "r") == 0){
                    cir -> r =  strtof(newAttribute -> value, NULL);
                    deleteAttribute(newAttribute);
                    return true;
                }else{

                    hold = updateOther(cir -> otherAttributes, newAttribute); 
                                  
                    return hold;
                }

            }else if(index > elemIndex){
                deleteAttribute(newAttribute);
                return false;
            }
        
            index = index + 1;
        
        }

   }else if(elemType == RECT){

       int index = 0;
       ListIterator iter_rect = createIterator(img -> rectangles);
       Rectangle *rect = NULL;
       bool hold;

        while ((rect = nextElement(&iter_rect)) != NULL){
        
            if(index == elemIndex){

                if(strcmp(newAttribute -> name, "x") == 0){
                    rect -> x =  strtof(newAttribute -> value, NULL);
                    deleteAttribute(newAttribute);
                    return true;
                }else if(strcmp(newAttribute -> name, "y") == 0){
                    rect -> y =  strtof(newAttribute -> value, NULL);
                    deleteAttribute(newAttribute);
                    return true;
                }else if(strcmp(newAttribute -> name, "width") == 0){
                    rect -> width =  strtof(newAttribute -> value, NULL);
                    deleteAttribute(newAttribute);
                    return true;
                }else if(strcmp(newAttribute -> name, "height") == 0){
                    rect -> height =  strtof(newAttribute -> value, NULL);
                    deleteAttribute(newAttribute);
                    return true;
                }else{

                    hold = updateOther(rect -> otherAttributes, newAttribute);
                    
                    return hold;
                }

            }else if(index > elemIndex){
                deleteAttribute(newAttribute);
                return false;
            }
        
            index = index + 1;
        
        }
   }else if(elemType == PATH){

       int index = 0;
       ListIterator iter_path = createIterator(img -> paths);
       Path *path = NULL;
       bool hold;

        while ((path = nextElement(&iter_path)) != NULL){
        
            if(index == elemIndex){

                if(strcmp(newAttribute -> name, "d") == 0){
                    
                    //free(path -> data);

                    //path -> data = malloc((strlen(newAttribute -> value) + 1) * sizeof(char));

                    strcpy(path -> data, newAttribute -> value);

                    deleteAttribute(newAttribute);
                    return true;

                }else{

                    hold = updateOther(path -> otherAttributes, newAttribute);
                   
                    return hold;
                }

                }else if(index > elemIndex){
                    deleteAttribute(newAttribute);
                    return false;
                }
        
            index = index + 1;
        
        } 
   }else if(elemType == GROUP){

       int index = 0;
       ListIterator iter_group = createIterator(img -> groups);
       Group *group = NULL;
       bool hold;

        while ((group = nextElement(&iter_group)) != NULL){
        
            if(index == elemIndex){

                if(group -> otherAttributes != NULL){
                    
                    hold = updateOther(group -> otherAttributes, newAttribute);
                   
                    return hold;
                }

            }else if(index > elemIndex){
                deleteAttribute(newAttribute);
                return false;
            }
        
            index = index + 1;
        
        }
   }
   deleteAttribute(newAttribute);
    return false;
}

/** Function to writing an SVG struct into a file in SVG format.
 *@pre
    SVG struct exists, is valid, and and is not NULL.
    fileName is not NULL, has the correct extension
 *@post SVG struct has not been modified in any way, and a file representing the
    SVG contents in SVG format has been created
 *@return a boolean value indicating success or failure of the write
 *@param
    doc - a pointer to a SVG struct
 	fileName - the name of the output file
 **/
bool writeSVG(const SVG* img, const char* fileName){


    if(img == NULL || fileName == NULL){
        return false;
    }

    if(!(checkAttr(img -> otherAttributes) && checkCircle(img -> circles) && checkPath(img -> paths) && checkRect(img -> rectangles) && validateGroup(img -> groups))){
        return false;
    }

    

    //Convert a struct to xml tree then write into file using demo file provided

    xmlDoc * newDoc = structToXMLTree(img);

       if(newDoc == NULL){

        return false;

        }

    /* 
     * Dumping document to stdio or file
     */
    int ret =  xmlSaveFormatFileEnc(fileName, newDoc, "UTF-8", 1);  //writting xml tree into svg readable file

    xmlFreeDoc(newDoc);
    xmlCleanupParser();
    if(ret == -1){

        
        return false;
    }else{

        return true;
    }

        
}



/** Function to adding an element - Circle, Rectngle, or Path - to an SVG
 *@pre
    SVG object exists, is valid, and and is not NULL.
    newElement is not NULL
 *@post The appropriate element was added correctly
 *@return N/A
 *@param
    struct - a pointer to an SVG struct
    elemType - enum value indicating elemtn to modify
    newElement - pointer to the element sgtruct (Circle, Rectngle, or Path)
 **/
void addComponent(SVG* img, elementType type, void* newElement){

    if(img == NULL || newElement == NULL){
        return;
    }

    if(type != RECT && type != CIRC && type != PATH){
        return;
    }

    if(type == CIRC){
        Circle * cir = (Circle*)newElement;
        if(cir != NULL){
            insertBack(img -> circles, cir);
        }
    }else if(type == RECT){
        Rectangle * rec = (Rectangle*)newElement;
        if(rec != NULL){
            insertBack(img -> rectangles, rec);
        }
    }else if(type == PATH){
        Path * path = (Path*)newElement;
        if(path != NULL){
            insertBack(img -> paths, path);
        }
    }
    
}


/** Function to converting an Attribute into a JSON string
*@pre Attribute is not NULL
*@post Attribute has not been modified in any way
*@return A string in JSON format
*@param event - a pointer to an Attribute struct
**/
char* attrToJSON(const Attribute *a){

    char *temp;

    if(a == NULL || a-> name == NULL || a-> value == NULL){
        char *temp = malloc(3*sizeof(char));
        strcpy(temp, "{}");
        return temp;
    }

    int len = strlen(a -> name) + strlen(a -> value) + 10000;

    temp = malloc(sizeof(char) * len);
    sprintf(temp, "{\"name\":\"%s\",\"value\":\"%s\"}", a-> name, a-> value);
    return temp;
}


char * jsonAttr(List * a){

    char *temp;
    if(a == NULL){

        temp = malloc(sizeof(char) + 1);
        strcpy(temp, "");
        
        return temp;
    }else{
        temp = malloc(sizeof(char) * 50);
        sprintf(temp,",\"numAttr\":%d", a -> length);

        return temp;
    }

}


/** Function to converting a Circle into a JSON string
*@pre Circle is not NULL
*@post Circle has not been modified in any way
*@return A string in JSON format
*@param event - a pointer to a Circle struct
**/
char* circleToJSON(const Circle *c){


    if(c == NULL){
        char* temp = malloc(4*sizeof(char));
        strcat(temp, "{}");
        return temp;
    }

    char *attr = jsonAttr(c -> otherAttributes);
    //char *unit = c -> units;
    char* attrList = attrListToJSON(c->otherAttributes);

    char *str = malloc((20 + 20 + 20 + strlen(c -> units) + strlen(attrList) + strlen(attr) + 128) * sizeof(char));

    sprintf(str, "{\"cx\":%.2f,\"cy\":%.2f,\"r\":%.2f%s,\"units\":\"%s\",\"otherAttrs\":%s}", c -> cx, c-> cy, c-> r, attr, c-> units, attrList);

    free(attr);
  
    //free(unit);

    return str;
}

/** Function to converting a Rectangle into a JSON string
*@pre Rectangle is not NULL
*@post Rectangle has not been modified in any way
*@return A string in JSON format
*@param event - a pointer to a Rectangle struct
**/
char* rectToJSON(const Rectangle *r){

    if(r == NULL){
        char* temp = malloc(4*sizeof(char));
        strcat(temp, "{}");
        return temp;
    }

    char *attr = jsonAttr(r -> otherAttributes);
   
    char* attrList = attrListToJSON(r->otherAttributes);

    char *str = malloc((20 + 20 + 20 + strlen(r -> units) + strlen(attrList) + strlen(attr) + 128) * sizeof(char));

    sprintf(str, "{\"x\":%.2f,\"y\":%.2f,\"w\":%.2f,\"h\":%.2f%s,\"units\":\"%s\",\"otherAttrs\":%s}", r -> x, r-> y, r-> width, r-> height, attr, r-> units, attrList);

    free(attr);
   
    return str;
}


/** Function to converting a Path into a JSON string
*@pre Path is not NULL
*@post Path has not been modified in any way
*@return A string in JSON format
*@param event - a pointer to a Path struct
**/
char* pathToJSON(const Path *p){

    char * temp;

    if(p == NULL){
        
        temp = malloc(4*sizeof(char));
        strcat(temp, "{}");
        return temp;
    }

    char *str;
    char *updatedStr;

    if(p -> data != NULL){

        str = jsonAttr(p -> otherAttributes);

        updatedStr = malloc(sizeof(char) * (65));
        strncpy(updatedStr, p -> data, 64);
        updatedStr[64] = '\0';

    }
    
    char* attrList = attrListToJSON(p->otherAttributes);

    int len = 65 + 25 + 20 + strlen(attrList);

    temp = malloc(sizeof(char) * len);

    sprintf(temp, "{\"d\":\"%s\"%s,\"otherAttrs\":%s}", updatedStr, str, attrList);

    free(updatedStr);
    free(str);
    
    return temp;

}

/** Function to converting a Group into a JSON string
*@pre Group is not NULL
*@post Group has not been modified in any way
*@return A string in JSON format
*@param event - a pointer to a Group struct
**/
char* groupToJSON(const Group *g){

    char *group = malloc(100000*sizeof(char));

    if(g == NULL){
        strcat(group, "{}");
        return group;
    }

    int rect = 0;
    int cir = 0;
    int jGroup = 0;
    int path = 0;
    char* attrList = attrListToJSON(g->otherAttributes);

    if(g -> groups != NULL){
        jGroup = getLength(g -> groups);
    } 

    if(g -> rectangles != NULL){
        rect = getLength(g -> rectangles);
    }     

    if(g -> paths != NULL){
        path = getLength(g -> paths);
    } 

    if(g -> circles != NULL){
        cir = getLength(g -> circles);
    } 

    int total = rect + cir + jGroup + path;

    sprintf(group, "{\"children\":%d,\"numAttr\":%d,\"otherAttrs\":%s}", total, getLength(g -> otherAttributes), attrList);

    return group;


}

/** Function to converting a list of Attribute structs into a JSON string
*@pre Attribute list is not NULL
*@post Attribute list has not been modified in any way
*@return A string in JSON format
*@param event - a pointer to a List struct
**/
char* attrListToJSON(const List *list){

    char *temp;

    if(list == NULL){

        temp = malloc(4*sizeof(char));
        strcat(temp, "[]");
        return temp;        
    }


    ListIterator iter = createIterator((List *)list);
    Attribute *attr = NULL;
    int counter = 0;
    temp = malloc(5*sizeof(char));

    strcpy(temp, "[");

    while((attr = nextElement(&iter)) != NULL){

        char *aJson = attrToJSON(attr);
        temp = realloc(temp, strlen(temp) + strlen(aJson) + 20);
        strcat(temp, aJson);
       
        free(aJson);
 
        if(counter != (getLength((List*)list) - 1)){
          strcat(temp, ",");  
        }

        counter = counter + 1;

    } 

    strcat(temp, "]");

    return temp;

}

/** Function to converting a list of Circle structs into a JSON string
*@pre Circle list is not NULL
*@post Circle list has not been modified in any way
*@return A string in JSON format
*@param event - a pointer to a List struct
**/
char* circListToJSON(const List *list){
    char *temp;

    if(list == NULL){

        temp = malloc(4*sizeof(char));
        strcat(temp, "[]");
        return temp;        
    }

    ListIterator iter = createIterator((List *)list);
    Circle *cir = NULL;
    int counter = 0;
    temp = malloc(5*sizeof(char));

    strcpy(temp, "[");

    while((cir = nextElement(&iter)) != NULL){  

        char *cirList= circleToJSON(cir);
        temp = realloc(temp, strlen(temp) + strlen(cirList) + 20);
        strcat(temp, cirList);
        
        free(cirList);

        if(counter != (getLength((List*)list) - 1)){
          strcat(temp, ",");  
        }

        counter = counter + 1;

    } 

    strcat(temp, "]");

    return temp;

}

/** Function to converting a list of Rectangle structs into a JSON string
*@pre Rectangle list is not NULL
*@post Rectangle list has not been modified in any way
*@return A string in JSON format
*@param event - a pointer to a List struct
**/
char* rectListToJSON(const List *list){
    char *temp;

    if(list == NULL){

        temp = malloc(4*sizeof(char));
        strcat(temp, "[]");
        return temp;        
    }

    ListIterator iter = createIterator((List *)list);
    Rectangle *rect = NULL;
    int counter = 0;
    temp = malloc(5*sizeof(char));

    strcpy(temp, "[");

    while((rect = nextElement(&iter)) != NULL){  

        char *rceList= rectToJSON(rect);
        temp = realloc(temp, strlen(temp) + strlen(rceList) + 20);
        strcat(temp, rceList);
        
        free(rceList);

        if(counter != (getLength((List*)list) - 1)){
          strcat(temp, ",");  
        }

        counter = counter + 1;

    } 

    strcat(temp, "]");

    return temp;


}

/** Function to converting a list of Path structs into a JSON string
*@pre Path list is not NULL
*@post Path list has not been modified in any way
*@return A string in JSON format
*@param event - a pointer to a List struct
**/
char* pathListToJSON(const List *list){

    char *temp;

    if(list == NULL){

        temp = malloc(4*sizeof(char));
        strcat(temp, "[]");
        return temp;        
    }

    ListIterator iter = createIterator((List *)list);
    Path *path = NULL;
    int counter = 0;
    temp = malloc(5*sizeof(char));

    strcpy(temp, "[");

    while((path = nextElement(&iter)) != NULL){  

        char *pathList= pathToJSON(path);
        temp = realloc(temp, strlen(temp) + strlen(pathList) + 20);
        strcat(temp, pathList);
        
        free(pathList);

        if(counter != (getLength((List*)list) - 1)){
          strcat(temp, ",");  
        }

        counter = counter + 1;

    } 

    strcat(temp, "]");

    return temp;


}

/** Function to converting a list of Group structs into a JSON string
*@pre Group list is not NULL
*@post Group list has not been modified in any way
*@return A string in JSON format
*@param event - a pointer to a List struct
**/
char* groupListToJSON(const List *list){

    char *temp;

    if(list == NULL){

        temp = malloc(4*sizeof(char));
        strcat(temp, "[]");
        return temp;        
    }

    ListIterator iter = createIterator((List *)list);
    Group *group = NULL;
    int counter = 0;

    temp = malloc(5*sizeof(char));

    strcpy(temp, "[");

    while((group = nextElement(&iter)) != NULL){  

        char *groupList= groupToJSON(group);
        temp = realloc(temp, strlen(temp) + strlen(groupList) + 20);
        strcat(temp, groupList);
        
        free(groupList);

        if(counter != (getLength((List*)list) - 1)){
          strcat(temp, ",");  
        }

        counter = counter + 1;

    } 

    strcat(temp, "]");

    return temp;

}

/** Function to converting an SVG into a JSON string
*@pre SVG is not NULL
*@post SVG has not been modified in any way
*@return A string in JSON format
*@param event - a pointer to an SVG struct
**/
char* SVGtoJSON(const SVG* img){

    char *svg;

    if(img == NULL){
        svg = malloc(4*sizeof(char));
        sprintf(svg, "{}");
        return svg;
    }

    svg = malloc(10000000*sizeof(char));

    int rect = 0;
    int cir = 0;
    int jGroup = 0;
    int path = 0;
   


    List * recList = getRects((SVG*)img);
    if(recList != NULL){
        rect = getLength(recList);
    }

    List * cirList = getCircles((SVG*)img);
    if(cirList != NULL){
        cir = getLength(cirList);
    }   

    List * pathList = getPaths((SVG*)img);  
    if(pathList != NULL){
        path = getLength(pathList);
    }

    List * groupList = getGroups((SVG*)img);  
    if(groupList != NULL){
        jGroup = getLength(groupList);
    }

    sprintf(svg, "{\"numRect\":%d,\"numCirc\":%d,\"numPaths\":%d,\"numGroups\":%d}", rect, cir, path, jGroup);
    svg = realloc(svg, strlen(svg)*sizeof(char) + 1);

    if(recList != NULL){
        dummyDelete(recList);
      
    }

    if(cirList != NULL){
        dummyDelete(cirList);
      
    }

    if(pathList != NULL){
        dummyDelete(pathList);
     
    }

    if(groupList != NULL){
        dummyDelete(groupList);
      
    }

    return svg;              

}

/* ******************************* Bonus A2 functions - optional for A2 *************************** */

/** Function to converting a JSON string into an SVG struct
*@pre JSON string is not NULL
*@post String has not been modified in any way
*@return A newly allocated and initialized SVG struct
*@param str - a pointer to a string
**/
SVG* JSONtoSVG(const char* svgString){

    if(svgString == NULL){
        return NULL;
    }else{

        SVG * hold = calloc(1, sizeof(SVG));

        hold -> otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
        hold -> rectangles = initializeList(&rectangleToString, &deleteRectangle, &compareRectangles);
        hold -> circles = initializeList(&circleToString, &deleteCircle, &compareCircles);
        hold -> paths = initializeList(&pathToString, &deletePath, &comparePaths);
        hold -> groups = initializeList(&groupToString, &deleteGroup, &compareGroups);

        char* s = strstr(svgString, "title") + 8;
        char* e = strstr(s, "\",\"");
        strncpy(hold->title, s, ((e - s) / sizeof(char)));

        s = strstr(e, "descr") + 8;
        e = strstr(s, "\"}");
        int length = ((e - s) / sizeof(char));

        int demo = 0;

        if(length > 255){
            demo = 255;
        }else{
            demo = length;
        }

        strncpy(hold->description, s, demo);

        return hold;
    }
}

char *trimChar(char *svg) {

    int count;

    char *hodl = malloc(sizeof(char) * (strlen(svg) + 1));

    for (count = 1; count < strlen(svg) - 1; count++)
    {

        hodl[count - 1] = svg[count];

    }

    hodl[count - 1] = '\0';

    return hodl;
}


/** Function to converting a JSON string into a Rectangle struct
*@pre JSON string is not NULL
*@post Rectangle has not been modified in any way
*@return A newly allocated and initialized Rectangle struct
*@param str - a pointer to a string
**/
Rectangle* JSONtoRect(const char* svgString){

    if(svgString == NULL){

    return NULL;   

    }else{

        char *pB[5];

        int pC = 0;

        char * pT;

        char *hodl = trimChar((char *)svgString);
        pT = strtok(hodl, ",");

        while (pT != NULL) {
            pB[pC] = malloc(sizeof(char) * (strlen(pT) + 1));
            strcpy(pB[pC], pT);
            pT = strtok(NULL, ",");
            pC++;
        }

        int i =0;  
        char * kV[10];
        int kC = 0;
        char * kT;

        for (i = 0; i < pC; i++) {

            kT = strtok(pB[i], ":");

            while (kT != NULL) {

                kV[kC] = malloc((strlen(kT) + 1) * sizeof(char));

                strcpy(kV[kC], kT);

                kT = strtok(NULL, ":");

                kC++;

            }
        }


        Rectangle * rectangle = NULL;
        if ((strcmp(kV[0], "\"x\"") == 0) && (strcmp(kV[2], "\"y\"") == 0) && (strcmp(kV[4], "\"w\"") == 0)
        && (strcmp(kV[6], "\"h\"") == 0) && (strcmp(kV[8], "\"units\"") == 0)) {

            rectangle = malloc(sizeof(Rectangle));

            rectangle->x = strtof(kV[1], NULL);

            rectangle->y = strtof(kV[3], NULL);

            rectangle->width = strtof(kV[5], NULL);

            rectangle->height = strtof(kV[7], NULL);

            char * unit = trimChar(kV[9]);

            strcpy(rectangle->units,unit);

            free(unit);

        }

        rectangle->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
        
        free(hodl);

        for (pC -= 1 ;pC >= 0; pC--) {
            free(pB[pC]);
        }

        for (kC -= 1 ;kC >= 0; kC--) {
            free(kV[kC]);
        }

        return rectangle;
    }
}


/** Function to converting a JSON string into a Circle struct
*@pre JSON string is not NULL
*@post Circle has not been modified in any way
*@return A newly allocated and initialized Circle struct
*@param str - a pointer to a string
**/
Circle* JSONtoCircle(const char* svgString){

if (svgString == NULL){
    return NULL;
}else{

    

    char *hodl = trimChar((char *)svgString);

    
    char *pB[4];

    int pC = 0;

    char * pT;
    pT = strtok(hodl, ",");

    while (pT != NULL) {

        pB[pC] = malloc(sizeof(char) * (strlen(pT) + 1));

        strcpy(pB[pC], pT);

        pT = strtok(NULL, ",");

        pC++;

    }

    
    char * kB[8];
    int kC = 0;
    char * kT;

    for (int i = 0; i < pC; i++) {

        kT = strtok(pB[i], ":");

        while (kT != NULL) {

            kB[kC] = malloc(sizeof(char) * (strlen(kT) + 1));

            strcpy(kB[kC], kT);

            kT = strtok(NULL, ":");

            kC++;
            
        }
    }

    Circle * circle = NULL;
    if ((strcmp(kB[0], "\"cx\"") == 0) && (strcmp(kB[2], "\"cy\"") == 0) && (strcmp(kB[4], "\"r\"") == 0)
    && (strcmp(kB[6], "\"units\"") == 0)) {
        circle = malloc(sizeof(Circle));

        circle->cx = strtof(kB[1], NULL);

        circle->cy = strtof(kB[3], NULL);

        circle->r = strtof(kB[5], NULL);

        char * unit = trimChar(kB[7]);
        strcpy(circle->units,unit);
        free(unit);

    }

    circle->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);


    free(hodl);

    for (pC -= 1 ;pC >= 0; pC--) {
        free(pB[pC]);
    }

    for (kC -= 1 ;kC >= 0; kC--) {
        free(kB[kC]);
    }

    return circle;
}

}

char* SVGtoJSON_FFI(char *file){

    SVG* img = createValidSVG(file, "parser/bin/svg.xsd");

    char * string;

    if(img != NULL){
        string = SVGtoJSON(img);
    }

    return string;


}


char* fullImgToJSON(char* filename) {
    if (filename == NULL) return NULL;
    SVG* image = createValidSVG(filename, "parser/bin/svg.xsd");
    if (image == NULL) return NULL;

    List* rects = getRects(image);
    char* rectsJSON = rectListToJSON(rects);
    List* circles = getCircles(image);
    char* circlesJSON = circListToJSON(circles);
    List* paths = getPaths(image);
    char* pathsJSON = pathListToJSON(paths);
    List* groups = getGroups(image);
    char* groupsJSON = groupListToJSON(groups);

    char* out = calloc(strlen(image->title) +
                       strlen(image->description) +
                       strlen(rectsJSON) +
                       strlen(circlesJSON) +
                       strlen(pathsJSON) +
                       strlen(groupsJSON) + 128, sizeof(char));

    sprintf(out, "{\"title\":\"%s\",\"description\":\"%s\",\"rectangles\":%s,\"circles\":%s,\"paths\":%s,\"groups\":%s}", image->title, image->description, rectsJSON, circlesJSON, pathsJSON, groupsJSON);



    return out;
}


char *updateOtherAttribute(char *file, char *elemType, float elementIndex, char *newOtherAttr, char *newOtherAttrVal)
{


    SVG *image = createValidSVG(file, "parser/bin/svg.xsd"); // create a valid image
    char *returnStr = calloc(6, sizeof(char));
   
    strcpy(returnStr, "false"); // default string it carries
    elementType eleType;

    int wrap = 0;
    
    if (strcmp("rect", elemType) == 0) {
        eleType = RECT;

        wrap = 1;
    } else if (strcmp("circ", elemType) == 0) {
        eleType = CIRC;

        wrap = 2;
    } else if (strcmp("path", elemType) == 0) {
        eleType = PATH;

        wrap = 3;
    } else if (strcmp("group", elemType) == 0) {
        eleType = GROUP;

        wrap = 4;
    } else if (strcmp("svg", elemType) == 0) {
        eleType = SVG_IMG;

        wrap = 5;
    }


    printf("%d\n", wrap);

    Attribute *newAttr = (Attribute *)calloc(1, sizeof(Attribute));
    newAttr->name = (char *)calloc(strlen(newOtherAttr) + 1, sizeof(char));
    
   
  

    strcpy(newAttr->name, newOtherAttr);
    strcpy(newAttr->value, newOtherAttrVal);
 

    elementIndex = elementIndex -1;
   bool huka = setAttribute(image, eleType, elementIndex, newAttr);
  

    printf("%d\n", huka);



    if (validateSVG(image, "parser/bin/svg.xsd")) { // valid
        free(returnStr);
        returnStr = (char *)calloc(5, sizeof(char));
        strcpy(returnStr, "true");

        printf("test 1");
        writeSVG(image, file); // write to file since it's valid
        printf("test 2");
    }

    if (image != NULL) {
        deleteSVG(image);
    }


    return returnStr;
}

/*Adding Shape*/
void addRectangle(char* filename, char* shapeType, float xCor, float yCor, float rwCor, float hCor ,char* units)
{

	printf("Data Received (Function)");
	printf("FileName: %s\n", filename);
	printf("shapeType: %s\n", shapeType);
	printf("x: %.6f\n", xCor);
	printf("y: %.6f\n", yCor);
	printf("rw: %.6f\n", rwCor);
	printf("h: %.6f\n", hCor);
	printf("units: %s\n", units);

    printf("test 1\n");
    char * file = calloc(4000, sizeof(char));
	strcpy(file, "uploads/");
	strcat(file, filename);

	//char * file = strcat("uploads/", filename);

    printf("test 1\n");
	SVG* svg = createValidSVG(file, "parser/bin/svg.xsd");
   
    
    printf("test 3\n");
    Rectangle * rec = (Rectangle *)malloc(sizeof(Rectangle));
	rec->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);

	rec->x = xCor;
	rec->y = yCor;
    rec->width = rwCor;
	rec->height = hCor;
	strcpy(rec->units, units);



	addComponent(svg, RECT, rec);


  
    
	/*This will write it to a file*/
	bool valid = writeSVG(svg, file);
	if(valid == false) return;

	
	free(file);

}

/*Adding Shape*/
void addCircle(char* filename, char* shapeType, float xCor, float yCor, float rwCor,char* units)
{

	printf("Data Received (Function)");
	printf("FileName: %s\n", filename);
	printf("shapeType: %s\n", shapeType);
	printf("x: %.6f\n", xCor);
	printf("y: %.6f\n", yCor);
	printf("rw: %.6f\n", rwCor);
	printf("units: %s\n", units);

    printf("test 1\n");
    char * file = calloc(4000, sizeof(char));
	strcpy(file, "uploads/");
	strcat(file, filename);

	//char * file = strcat("uploads/", filename);

    printf("test 1\n");
	SVG* svg = createValidSVG(file, "parser/bin/svg.xsd");
   
    
    printf("test 3\n");
		Circle * cir = (Circle *)malloc(sizeof(Circle));
		cir->otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);

		cir->cx = xCor;
		cir->cy = yCor;
		cir->r = rwCor;
		strcpy(cir->units, units);



		addComponent(svg, CIRC, cir);


  
    
	/*This will write it to a file*/
	bool valid = writeSVG(svg, file);
	if(valid == false) return;

	
	free(file);

}

/* Scale Shape */
void scaleRect(char* filename, char* scaleFactor)
{
	/* PRINT STATMENTS */
	printf("\n\nData Received (Function)");
	printf("FileName: %s\n", filename);

	printf("x: %s\n", scaleFactor);

    printf("test 1\n");
    char * file = calloc(4000, sizeof(char));
	strcpy(file, "uploads/");
	strcat(file, filename);

	//char * file = strcat("uploads/", filename);

    printf("test 1\n");
	SVG* svg = createValidSVG(file, "parser/bin/svg.xsd");


		List* rects = getRects(svg);


		if(getLength(rects) != 0)
		{
			ListIterator inner_itr = createIterator(rects);
			Rectangle * rectTemp = nextElement(&inner_itr);
			while(rectTemp !=NULL){
				rectTemp->x *= atof(scaleFactor);
				rectTemp->y *= atof(scaleFactor);
				rectTemp = nextElement(&inner_itr);
			}

		}

	/*This will write it to a file*/
	bool valid = writeSVG(svg, file);
	if(valid == false) return;

	
	free(file);
}

/* Scale Shape */
void scaleCircle(char* filename, char* scaleFactor)
{
	/* PRINT STATMENTS */
	printf("\n\nData Received (Function)");
	printf("FileName: %s\n", filename);

	printf("x: %s\n", scaleFactor);

    printf("test 1\n");
    char * file = calloc(4000, sizeof(char));
	strcpy(file, "uploads/");
	strcat(file, filename);

	//char * file = strcat("uploads/", filename);

    printf("test 1\n");
	SVG* svg = createValidSVG(file, "parser/bin/svg.xsd");


		List* circle = getCircles(svg);
		//printList(circle, "Circles");

		if(getLength(circle) != 0)
		{
			ListIterator inner_itr = createIterator(circle);
			Circle * circleTemp = nextElement(&inner_itr);
			while(circleTemp !=NULL){
				circleTemp->cx *= atof(scaleFactor);
				circleTemp->cy *= atof(scaleFactor);
				circleTemp = nextElement(&inner_itr);
			}
			printf("\n\nData Scaled: \n");

		}

	/*This will write it to a file*/
	bool valid = writeSVG(svg, file);
	if(valid == false) return;

	
	free(file);
}

char * createNewSVGFile(char * filename, char * title, char * description){
    char * toReturn = malloc(sizeof(char)*64);
    SVG * tmpSVG = malloc(sizeof(SVG));
    tmpSVG -> otherAttributes = initializeList(&attributeToString, &deleteAttribute, &compareAttributes);
    tmpSVG -> rectangles = initializeList(&rectangleToString, &deleteRectangle, &compareRectangles);
    tmpSVG -> circles = initializeList(&circleToString, &deleteCircle, &compareCircles);
    tmpSVG -> paths = initializeList(&pathToString, &deletePath, &comparePaths);
    tmpSVG -> groups = initializeList(&groupToString, &deleteGroup, &compareGroups);
    strcpy(tmpSVG->namespace, "http://www.w3.org/2000/svg");
    strcpy(tmpSVG->title, title);
    strcpy(tmpSVG->description, description);
    bool status = writeSVG(tmpSVG, filename);
    if (status == true){
        strcpy(toReturn, "successfully created");
    }
    else {
        strcpy(toReturn, "creation failed");
    }
    return toReturn;
    
}

bool saveTitle(char* filename, char* newTitle) {
    if (filename == NULL  || newTitle == NULL) return false;

    SVG* image = createValidSVG(filename, "parser/bin/svg.xsd");
    if (image == NULL) return false;

    printf("Tessssssssssst\n");

    strcpy(image->title, newTitle);
    bool result = writeSVG(image, filename);


    return result;
}

bool saveDesc(char* filename, char* newDesc) {
    if (filename == NULL  || newDesc == NULL) return false;

    SVG* image = createValidSVG(filename, "parser/bin/svg.xsd");
    if (image == NULL) return false;

    strcpy(image->description, newDesc);
    bool result = writeSVG(image, filename);
  

    return result;
}

bool validateFile (char* filename) {
    if (filename == NULL) return false;

    SVG* image = createValidSVG(filename, "parser/bin/svg.xsd");

    if (image == NULL) {
        return false;
    } else {
        
        return true;
    }
}