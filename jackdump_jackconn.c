#include <stdio.h>
#include <jack/jack.h>


int main(int ac, char **av)
{
  jack_client_t  *client = NULL;
  jack_status_t  status;
  jack_options_t jack_options = JackNoStartServer;
  jack_port_t    *port = NULL;
  int            flags = 0;
  const char     **port_name = NULL,
    **port_conn = NULL,
    **ports = NULL,
    **conns = NULL;

  client = jack_client_open("jackdump_jackconn", jack_options, &status, NULL);
  if (client == NULL) {
    if (status & JackServerFailed) {
      fprintf(stderr, "JACK server not running\n");
    } else {
      fprintf(stderr, "jack_client_open() failed, "
              "status = 0x%2.0x\n", status);
    }
    return 1;
  }

  ports = jack_get_ports(client, NULL, NULL, 0);
  if (ports != NULL)
    {
      for (port_name = ports;
           *port_name != NULL;
           port_name++)
        {
          port = jack_port_by_name(client, *port_name);
          flags = jack_port_flags(port);
          if (flags & JackPortIsOutput)
            {
              conns = jack_port_get_all_connections(client, jack_port_by_name(client, *port_name));
              if (conns != NULL)
                {
                  for (port_conn = conns;
                       *port_conn != NULL;
                       port_conn++)
                    printf("jack_connect '%s' '%s'\n", *port_name, *port_conn);
                  jack_free(conns);
                }
            }
        }
      jack_free(ports);
    }
  jack_client_close(client);
  return 0;
}
