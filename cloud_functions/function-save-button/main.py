import base64
import sqlalchemy
import os
import pandas

def save_button(event, context):
    receive = base64.b64decode(event['data'])
    protocol = receive[:4]
    address = receive[4:6]
    command = receive[6:8]
    name = receive[8:].decode('utf-8')

    row_data = pandas.DataFrame([{
        "protocol":protocol,
        "address":address,
        "command":command,
        "name":name
    }])

    db_user = os.environ["DB_USER"]
    db_pass = os.environ["DB_PASS"]
    db_name = os.environ["DB_NAME"]
    db_socket_dir = os.environ.get("DB_SOCKET_DIR", "/cloudsql")
    instance_connection_name = os.environ["INSTANCE_CONNECTION_NAME"]

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

    row_data.to_sql('commands',con=pool,if_exists="append",index=False)
    print(row_data)
     

