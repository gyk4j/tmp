import {
    MDBTable, 
    MDBTableBody,
    MDBProgress,
    MDBProgressBar,
} from 'mdb-react-ui-kit';

export default function TabStatistics({
    total,
    transferred,
    duration
  }) {
    return (
      <div>
        <div className="my-5">
          <MDBProgress height='32'>
            <MDBProgressBar 
              width={Math.round((transferred / total) * 100)} 
              valuemin={0} 
              valuemax={100}>
              {Math.round((transferred / total) * 100)}%
            </MDBProgressBar>
          </MDBProgress>
        </div>
        <MDBTable small>
          <MDBTableBody>
            <tr>
              <th scope='row'>Total Bytes (Kb)</th>
              <td>{total.toLocaleString()}</td>

              <th scope='row'>Duration</th>
              <td>{ Math.floor(duration / 3600) } hr { Math.floor(duration /60) } min {duration % 60} sec</td>
            </tr>
            <tr>
              <th scope='row'>Total Bytes Transferred (Kb)</th>
              <td>{transferred.toLocaleString()}</td>

              <th scope='row'>Average Transfer Speed (Kbps)</th>
              <td>{ (transferred / duration).toLocaleString() }</td>
            </tr>
            
          </MDBTableBody>
        </MDBTable>
      </div>
    )
  }