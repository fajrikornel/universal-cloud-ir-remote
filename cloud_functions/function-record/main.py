import logging
import os

from google.cloud import iot_v1

project_id  = os.environ['GCP_PROJECT']

registry_id = os.environ['REGISTRY_ID']
gcp_region  = os.environ['GCP_REGION']
device_id   = os.environ['DEVICE_ID']

def record(request):
    logging.info(request.headers.keys())
    
    button = request.args.get('button')
    
    binary_data = b'\xFE' + bytes(button,'ascii')
    device_name = 'projects/{}/locations/{}/registries/{}/devices/{}'.format(project_id,
                                                                             gcp_region,
                                                                             registry_id,
                                                                             device_id)

    client = iot_v1.DeviceManagerClient()

    client.send_command_to_device(name=device_name, binary_data=binary_data)

    headers = {
        'Access-Control-Allow-Origin': '*'
    }

    return ('Trigger success!', 200, headers)