#include <bits/stdc++.h>
#include <cstdlib>

using namespace std;
// #define int  long long 
// #define mod 1000000007

bool is_deleted[2000];

typedef struct spell_info{
    int id;
    char incantation[50];
    char name[50];
    char effect[50];
    char light[50];
} spell_info;

void remove_space(char str[])
{
    int i = 0;

    while(str[i] != '\0'){
        if(str[i] == ' ')
            str[i] = ' ';
        i++;
    }
}

void push(int id, const char* incantation, const char* name, const char* effect, const char* light, vector<spell_info> &v)
{
    spell_info x;
    x.id = id;
    strcpy(x.incantation, incantation);
    strcpy(x.name, name);
    strcpy(x.effect, effect);
    strcpy(x.light, light);
    v.push_back(x);
}

void insert(int id, const char* incantation, const char* name, const char* effect, const char* light, vector<spell_info> &v)
{
    strcpy(v[id-1].incantation, incantation);
    strcpy(v[id-1].name, name);
    strcpy(v[id-1].effect, effect);
    strcpy(v[id-1].light, light);
    is_deleted[id-1] = false;
}

void update(int id, const char* content, const char* update, vector<spell_info> &v)
{
    if(strcmp(content,"incantation") == 0)
        strcpy(v[id-1].incantation, update);
    else if(strcmp(content,"name") == 0)
        strcpy(v[id-1].name, update);
    else if(strcmp(content,"effect") == 0)
        strcpy(v[id-1].effect, update);
    else if(strcmp(content,"light") == 0)
        strcpy(v[id-1].light, update);

    is_deleted[id-1] = false;
}

void _delete(int id, vector<spell_info> &v)
{
    if(is_deleted[id-1] == true){
        printf("Can't delete, entry already empty\n");
        return;
    }

    strcpy(v[id-1].incantation, " ");
    strcpy(v[id-1].name, " ");
    strcpy(v[id-1].effect, " ");
    strcpy(v[id-1].light, " ");
    is_deleted[id-1] = true;
}

void search(int id, vector<spell_info> v)
{
    id--;

    printf("Spell ID: %d\nIncantation: %s\nSpell Name: %s\nEffect: %s\nLight: %s\n\n", v[id].id, v[id].incantation, v[id].name, v[id].effect, v[id].light);
}

signed main()
{
    char temp[500];
    vector<spell_info> v;

    FILE* file = fopen("spells.txt", "r");
    fscanf(file, "%[^\n]", temp);

    ///Reading the file content into v vector
    while(1){
        spell_info x;
        strcpy(x.light, "");
        x.id = -1;

        int p = fscanf(file, "%d,%[^,],%[^,],%[^,],%[^\n]", &x.id, x.incantation, x.name, x.effect, x.light);
        if(x.id == -1)
            break;

        remove_space(x.incantation);
        remove_space(x.name);
        remove_space(x.effect);
        remove_space(x.light);
        v.push_back(x);
    }

    ///Deleting entries from the file.
    // _delete(5, v);
    // _delete(5, v);

    ///Inserting new rows in the database file.
    // insert(5, "Fire/Dark type", "Incineroar", "Darkest Lariat", "Blaze", v);

    ///Inserting a new row at the end
    // push(v.size()+1, "Fire/Flying type", "Ho-Oh", "Sacred Flame", "Pressure", v);
    // push(v.size()+1, "Psychic type", "Necrozma", "Photon Geysar", "Beast Boost", v);

    ///Updating certain columns for some entries in the file.
    // update(62, "name", "Moltres", v);
    // update(32, "effect", "Brave Bird", v);

    ///Searching entries from the file based on a unique ID.
    // search(62, v);
    // search(1, v);
    // search(17, v);

    //reopening the file for overwriting
    fclose(file);
    fopen("spells.txt", "w");

    //overwriting the file
    fprintf(file, "%s\n", temp);
    for(int i=0; i<v.size(); i++){
        fprintf(file, "%d,%s,%s,%s,%s\n", v[i].id, v[i].incantation, v[i].name, v[i].effect, v[i].light);
    }

    fclose(file);

    return 0;
}
