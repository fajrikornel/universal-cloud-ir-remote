# function-save-button

This function processes the published IR button record from the Cloud Pub/Sub to the Cloud SQL database.

Environment Variables defined in this function are:

|Environment Variable |    Value                |
|---------------------|-------------------------|
| DB_USER             | Cloud SQL database user |
| DB_PASS             | Cloud SQL database pass |
| INSTANCE_CONNECTION_NAME | Cloud SQL instance connection name |