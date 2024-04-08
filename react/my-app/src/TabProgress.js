import {
    MDBTable, 
    MDBTableHead, 
    MDBTableBody,
    MDBIcon,
} from 'mdb-react-ui-kit';

import ProgressLabel from './ProgressLabel';

export default function TabProgress({
  backups
}) {
  return (
      <MDBTable striped bordered>
      <MDBTableHead>
        <tr className="table-secondary">
          <th scope='col'>
              <MDBIcon
                    className='me-2' 
                    far 
                    icon="clock" />
              Backup Time
          </th>
          <th scope='col'>
              <MDBIcon
                    className='me-2' 
                    fas 
                    icon="table" />
              Database
          </th>
          <th scope='col'>
              <MDBIcon
                    className='me-2' 
                    far 
                    icon="envelope" />
              Email
          </th>
          <th scope='col'>
              <MDBIcon
                    className='me-2' 
                    far 
                    icon="file-alt" />
              File
          </th>
          <th scope='col'>
              <MDBIcon
                    className='me-2' 
                    fas 
                    icon="globe-asia" />
              Web
          </th>
        </tr>
      </MDBTableHead>
      <MDBTableBody>
        {
          backups.map((backup, index) => (
            <tr key={index}>
              <td>{backup.time.toLocaleString()}</td>
              <td><ProgressLabel progress={backup.database} /></td>
              <td><ProgressLabel progress={backup.email} /></td>
              <td><ProgressLabel progress={backup.file} /></td>
              <td><ProgressLabel progress={backup.web} /></td>
            </tr>
          ))
        }
      </MDBTableBody>
    </MDBTable>
  )
}