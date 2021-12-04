import logging
import os
import sqlalchemy
import pandas

from google.cloud import iot_v1

project_id  = os.environ['GCP_PROJECT']

registry_id = os.environ['REGISTRY_ID']
gcp_region  = os.environ['GCP_REGION']
device_id   = os.environ['DEVICE_ID']

def transmit(request):
    db_user = os.environ["DB_USER"]
    db_pass = os.environ["DB_PASS"]
    db_name = os.environ["DB_NAME"]
    db_socket_dir = os.environ.get("DB_SOCKET_DIR", "/cloudsql")
    instance_connection_name = os.environ["INSTANCE_CONNECTION_NAME"]

    # If the user passed in a message variable, then update our incoming message to match
    logging.info(request.headers.keys())

    #query params
    button = request.args.get('button')
    time = int(request.args.get('time'))

    if (button == None or time == None):
      return '500'

    #process microseconds time to hex
    time_hex = format(time,'x')
    if (len(time_hex) < 8):
      time_hex = (8-len(time_hex))*'0' + time_hex
    else:
      time_hex = time_hex[:8]

    pool = sqlalchemy.create_engine(
        # Equivalent URL:
        # mysql+pymysql://<db_user>:<db_pass>@/<db_name>?unix_socket=<socket_path>/<cloud_sql_instance_name>
        sqlalchemy.engine.url.URL.create(
            drivername="mysql+pymysql",
            username=db_user,  # e.g. "my-database-user"
            password=db_pass,  # e.g. "my-database-password"
            database=db_name,  # e.g. "my-database-name"
            query={
                "unix_socket": "{}/{}".format(
                    db_socket_dir,  # e.g. "/cloudsql"
                    instance_connection_name)  # i.e "<PROJECT-NAME>:<INSTANCE-REGION>:<INSTANCE-NAME>"
            }
        )
    )
    
    row_command = pandas.read_sql(f"SELECT protocol, address, command FROM commands WHERE name=\'{button}\'",pool)

    binary_data = b'\xff' + bytes.fromhex(time_hex) +bytes(''.join(row_command.values[0].astype('str')),'ascii')

    device_name = 'projects/{}/locations/{}/registries/{}/devices/{}'.format(project_id,
                                                                             gcp_region,
                                                                             registry_id,
                                                                             device_id)

    client = iot_v1.DeviceManagerClient()

    logging.info("Transmitting an IR code")
    client.send_command_to_device(name=device_name, binary_data=binary_data)

    headers = {
        'Access-Control-Allow-Origin': '*'
    }

    return ('Success', 200, headers)