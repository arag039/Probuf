#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "addressbook.pb.h"
#include "lib.h"

unsigned database_size;
foo::Person *database;

int main(int argc, char**argv)
{
  ProtobufC_RPC_Server *server;
  ProtobufC_RPC_AddressType address_type=0;
  const char *name = NULL;
  unsigned i;

  for (i = 1; i < (unsigned) argc; i++)
    {
      if (starts_with (argv[i], "--port="))
        {
          address_type = PROTOBUF_C_RPC_ADDRESS_TCP;
          name = strchr (argv[i], '=') + 1;
        }
      else if (starts_with (argv[i], "--unix="))
        {
          address_type = PROTOBUF_C_RPC_ADDRESS_LOCAL;
          name = strchr (argv[i], '=') + 1;
        }
      else if (starts_with (argv[i], "--database="))
        {
          load_database (strchr (argv[i], '=') + 1);
        }
      else
        usage ();
    }

  if (database_size == 0)
    die ("missing --database=FILE (try --database=example.database)");
  if (name == NULL)
    die ("missing --port=NUM or --unix=PATH");

  server = protobuf_c_rpc_server_new (address_type, name, (ProtobufCService *) &the_dir_lookup_service, NULL);

  for (;;)
    protobuf_c_dispatch_run (protobuf_c_dispatch_default ());
  return 0;
}
