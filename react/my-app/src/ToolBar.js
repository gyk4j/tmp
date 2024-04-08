import {
    MDBCard,
    MDBCardBody,
    MDBContainer,
    MDBRow,
    MDBCol,
    MDBIcon,
    MDBBtn,
} from 'mdb-react-ui-kit';

export default function ToolBar({
  transferState,
  startOnClick,
  sendCompletedOnClick,
  sendDeltaNowOnClick,
  sendLastDeltaOnClick,
  checkQuotaOnClick,
  exportLogsOnClick,
  archiveOnClick
}) {
  const TRANSFER_STATES = {
    NOT_STARTED: new TransferState(true, false, false, false),
    STARTING: new TransferState(false, false, false, false),
    STARTED: new TransferState(true, true, true, true),
    STOPPING: new TransferState(false, false, false, false),
    ENDED: new TransferState(false, false, false, false)
  }

  let state = TRANSFER_STATES[transferState]

  console.log(state)

  return (
    <div className="m-3">
      <MDBCard>
        <MDBCardBody>

          <MDBContainer>
            <MDBRow className='row-cols-4 gy-4'>
            
              <MDBCol className="d-grid gap-2 col-3 mx-auto">
                  <MDBBtn 
                    onClick={startOnClick} 
                    disabled={ !state.start } 
                    color={ state.start? "primary" : "secondary"}>
                    <MDBIcon
                      className='me-2' 
                      fas 
                      icon={ transferState === 'NOT_STARTED' ? 'play' : 'hourglass-start' } />
                    { transferState === 'NOT_STARTED' ? 'Start Backup' : 'Change Interval' }
                  </MDBBtn>
              </MDBCol>
              
              <MDBCol className="d-grid gap-2 col-3 mx-auto">
                <MDBBtn 
                  onClick={sendCompletedOnClick} 
                  disabled={ !state.resumeDeltaTransfer } 
                  color={ state.resumeDeltaTransfer? "primary" : "secondary"}>
                  <MDBIcon className='me-2' fas icon='redo' />
                  Resume Delta Transfer
                </MDBBtn>
              </MDBCol>

              <MDBCol className="d-grid gap-2 col-3 mx-auto">
                <MDBBtn 
                  onClick={sendDeltaNowOnClick} 
                  disabled={ !state.sendDeltaNow } 
                  color={ state.sendDeltaNow? "primary" : "secondary"}>
                  <MDBIcon className='me-2' fas icon='forward' />
                  Send Delta Now
                </MDBBtn>
              </MDBCol>

              <MDBCol className="d-grid gap-2 col-3 mx-auto">
                <MDBBtn 
                  onClick={sendLastDeltaOnClick} 
                  disabled={ !state.sendLastDelta } 
                  color={ state.sendLastDelta? "primary" : "secondary"}>
                  <MDBIcon className='me-2' fas icon='stop' />
                  Send Last Delta
                </MDBBtn>
              </MDBCol>

            </MDBRow>

            <MDBRow className='row-cols-4 gy-4'>

              <MDBCol className="d-grid gap-2 col-3 mx-auto">
                <MDBBtn>
                  <MDBIcon className='me-2' fas icon='sync' />
                  Sync Progress Status
                </MDBBtn>
              </MDBCol>

              <MDBCol className="d-grid gap-2 col-3 mx-auto">
                <MDBBtn onClick={checkQuotaOnClick}>
                  <MDBIcon className='me-2' fas icon='hdd' />
                  Check Quota
                </MDBBtn>  
              </MDBCol>

              <MDBCol className="d-grid gap-2 col-3 mx-auto">
                <MDBBtn onClick={exportLogsOnClick}>
                  <MDBIcon className='me-2' fas icon='file-export' />
                  Export Logs
                </MDBBtn>       
              </MDBCol>

              <MDBCol className="d-grid gap-2 col-3 mx-auto">
                <MDBBtn onClick={archiveOnClick}>
                  <MDBIcon className='me-2' fas icon='archive' />
                  Archive
                </MDBBtn>
              </MDBCol>

            </MDBRow>
          </MDBContainer>  
        </MDBCardBody>
      </MDBCard>
    </div>
  )
}

class TransferState {
  constructor(start, resumeDeltaTransfer, sendDeltaNow, sendLastDelta) {
    this.start = start
    this.resumeDeltaTransfer = resumeDeltaTransfer
    this.sendDeltaNow = sendDeltaNow
    this.sendLastDelta = sendLastDelta
  }
}
