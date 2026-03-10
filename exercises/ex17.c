/*
 * Exercise 17 - Learn C the Hard Way
 *
 * Modified to accept MAX_DATA and MAX_ROWS as command-line parameters.
 * These are stored in the Database struct and written to the file, allowing
 * databases of arbitrary size to be created.
 *
 * Usage: ex17 <dbfile> <action> [action params]
 *   Actions:
 *     c [max_data] [max_rows]  - create a new database (defaults: 512, 100)
 *     g <id>                   - get record by id
 *     s <id> <name> <email>    - set record
 *     d <id>                   - delete record
 *     l                        - list all records
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct Address {
    int id;
    int set;
    char *name;
    char *email;
};

struct Database {
    int max_data;
    int max_rows;
    struct Address *rows;
};

struct Connection {
    FILE *file;
    struct Database *db;
};

void die(const char *message)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n",
            addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
    struct Database *db = conn->db;

    int rc = fread(&db->max_data, sizeof(int), 1, conn->file);
    if(rc != 1) die("Failed to load database header (max_data).");

    rc = fread(&db->max_rows, sizeof(int), 1, conn->file);
    if(rc != 1) die("Failed to load database header (max_rows).");

    db->rows = malloc(sizeof(struct Address) * db->max_rows);
    if(!db->rows) die("Memory error");

    for(int i = 0; i < db->max_rows; i++) {
        struct Address *addr = &db->rows[i];

        addr->name = malloc(db->max_data);
        if(!addr->name) die("Memory error");
        addr->email = malloc(db->max_data);
        if(!addr->email) die("Memory error");

        rc = fread(&addr->id, sizeof(int), 1, conn->file);
        if(rc != 1) die("Failed to load address id.");
        rc = fread(&addr->set, sizeof(int), 1, conn->file);
        if(rc != 1) die("Failed to load address set.");
        rc = fread(addr->name, db->max_data, 1, conn->file);
        if(rc != 1) die("Failed to load address name.");
        rc = fread(addr->email, db->max_data, 1, conn->file);
        if(rc != 1) die("Failed to load address email.");
    }
}

struct Connection *Database_open(const char *filename, char mode, int max_data, int max_rows)
{
    struct Connection *conn = malloc(sizeof(struct Connection));
    if(!conn) die("Memory error");

    conn->db = malloc(sizeof(struct Database));
    if(!conn->db) {
        free(conn);
        die("Memory error");
    }

    conn->db->rows = NULL;

    if(mode == 'c') {
        conn->file = fopen(filename, "w");
        if(!conn->file) {
            free(conn->db);
            free(conn);
            die("Failed to open the file");
        }
        conn->db->max_data = max_data;
        conn->db->max_rows = max_rows;
    } else {
        conn->file = fopen(filename, "r+");
        if(!conn->file) {
            free(conn->db);
            free(conn);
            die("Failed to open the file");
        }
        Database_load(conn);
    }

    return conn;
}

void Database_close(struct Connection *conn)
{
    if(conn) {
        if(conn->file) fclose(conn->file);
        if(conn->db) {
            if(conn->db->rows) {
                for(int i = 0; i < conn->db->max_rows; i++) {
                    struct Address *cur = &conn->db->rows[i];
                    if(cur->name) free(cur->name);
                    if(cur->email) free(cur->email);
                }
                free(conn->db->rows);
            }
            free(conn->db);
        }
        free(conn);
    }
}

void Database_write(struct Connection *conn)
{
    struct Database *db = conn->db;
    rewind(conn->file);

    int rc = fwrite(&db->max_data, sizeof(int), 1, conn->file);
    if(rc != 1) die("Failed to write database header (max_data).");

    rc = fwrite(&db->max_rows, sizeof(int), 1, conn->file);
    if(rc != 1) die("Failed to write database header (max_rows).");

    for(int i = 0; i < db->max_rows; i++) {
        struct Address *addr = &db->rows[i];

        rc = fwrite(&addr->id, sizeof(int), 1, conn->file);
        if(rc != 1) die("Failed to write address id.");
        rc = fwrite(&addr->set, sizeof(int), 1, conn->file);
        if(rc != 1) die("Failed to write address set.");
        rc = fwrite(addr->name, db->max_data, 1, conn->file);
        if(rc != 1) die("Failed to write address name.");
        rc = fwrite(addr->email, db->max_data, 1, conn->file);
        if(rc != 1) die("Failed to write address email.");
    }

    rc = fflush(conn->file);
    if(rc == -1) die("Cannot flush database.");
}

void Database_create(struct Connection *conn)
{
    struct Database *db = conn->db;

    db->rows = malloc(sizeof(struct Address) * db->max_rows);
    if(!db->rows) die("Memory error");

    for(int i = 0; i < db->max_rows; i++) {
        struct Address *addr = &db->rows[i];
        addr->id = i;
        addr->set = 0;
        addr->name = malloc(db->max_data);
        if(!addr->name) die("Memory error");
        addr->email = malloc(db->max_data);
        if(!addr->email) die("Memory error");
        memset(addr->name, 0, db->max_data);
        memset(addr->email, 0, db->max_data);
    }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    struct Database *db = conn->db;
    struct Address *addr = &db->rows[id];
    if(addr->set) die("Already set, delete it first");

    addr->set = 1;
    char *res = strncpy(addr->name, name, db->max_data - 1);
    if(!res) die("Name copy failed");
    addr->name[db->max_data - 1] = '\0';

    res = strncpy(addr->email, email, db->max_data - 1);
    if(!res) die("Email copy failed");
    addr->email[db->max_data - 1] = '\0';
}

void Database_get(struct Connection *conn, int id)
{
    struct Database *db = conn->db;
    struct Address *addr = &db->rows[id];

    if(addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set");
    }
}

void Database_delete(struct Connection *conn, int id)
{
    struct Database *db = conn->db;
    struct Address *addr = &db->rows[id];

    memset(addr->name, 0, db->max_data);
    memset(addr->email, 0, db->max_data);
    addr->set = 0;
}

void Database_list(struct Connection *conn)
{
    struct Database *db = conn->db;

    for(int i = 0; i < db->max_rows; i++) {
        struct Address *cur = &db->rows[i];

        if(cur->set) {
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[])
{
    if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]");

    char *filename = argv[1];
    char action = argv[2][0];

    int max_data = 512;
    int max_rows = 100;

    if(action == 'c') {
        if(argc >= 4) max_data = atoi(argv[3]);
        if(argc >= 5) max_rows = atoi(argv[4]);
        if(max_data <= 0) die("Invalid MAX_DATA");
        if(max_rows <= 0) die("Invalid MAX_ROWS");
    }

    struct Connection *conn = Database_open(filename, action, max_data, max_rows);
    int id = 0;

    if(argc > 3 && action != 'c') id = atoi(argv[3]);
    if(action != 'c' && action != 'l' && id >= conn->db->max_rows)
        die("There's not that many records.");

    switch(action) {
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;

        case 'g':
            if(argc != 4) die("Need an id to get");

            Database_get(conn, id);
            break;

        case 's':
            if(argc != 6) die("Need id, name, email to set");

            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if(argc != 4) die("Need id to delete");

            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;
        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list");
    }

    Database_close(conn);

    return 0;
}
