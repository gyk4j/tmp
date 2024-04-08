import {
    MDBTable, 
    MDBTableHead, 
    MDBTableBody,
    MDBProgress,
    MDBProgressBar,
    MDBIcon,
} from 'mdb-react-ui-kit';

export default function TabQuota({
  quotas
}) {
  const format = (quota) => {
    let usage = quota.used / quota.total;
    
    if(usage >= 0.9)
      return "danger"
    else if(usage >= 0.75)
      return "warning"
    else if(usage >= 0.66)
      return "info"
    else
      return "success"
  }

  return (
    <MDBTable small bordered>
      <MDBTableHead>
        <tr className="table-secondary">
          <th scope='col'>
          <MDBIcon
            className='me-2' 
            far 
            icon="folder" />
            Folder
          </th>
          <th scope='col'>
            <MDBIcon
              className='me-2' 
              fas 
              icon="percent" />
            Usage
          </th>
          <th scope='col'>
            <MDBIcon
              className='me-2' 
              fas 
              icon="battery-empty" />
            Total (MB)
          </th>
          <th scope='col'>
            <MDBIcon
              className='me-2' 
              fas 
              icon="battery-three-quarters" />
            Used (MB)
          </th>
          <th scope='col'>
            <MDBIcon
              className='me-2' 
              fas 
              icon="battery-quarter" />
            Free (MB)
          </th>
        </tr>
      </MDBTableHead>
      <MDBTableBody>
        {
          quotas.map((quota, index) => (
            <tr key={index}>
              <th scope='row'>{quota.directory}</th>
              <td>
                <MDBProgress height="24">
                  <MDBProgressBar 
                    bgColor={format(quota)}
                    width={Math.round((quota.used / quota.total) * 100)} 
                    valuemin={0} 
                    valuemax={100}>
                    {Math.round((quota.used / quota.total) * 100)}%
                  </MDBProgressBar>
                </MDBProgress>
              </td>
              <td>{quota.total}</td>
              <td>{quota.used}</td>
              <td>{quota.total - quota.used}</td>
            </tr>
          ))
        }
      </MDBTableBody>
    </MDBTable>
  )
}
