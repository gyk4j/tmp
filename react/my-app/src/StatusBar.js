import {
    MDBCard,
    MDBCardBody,
    MDBContainer,
    MDBRow, 
    MDBCol,
    MDBDropdown, 
    MDBDropdownMenu, 
    MDBDropdownToggle, 
    MDBDropdownItem,
} from 'mdb-react-ui-kit';

export default function StatusBar({ 
    isMain, 
    isOnline,
    interval,
    changeIntervalOnChange,
    countdown,
    startTime,
    endTime
    }) {
    const toCountDownString = (countdown) => {
        let s = ""
        let hr = Math.floor(countdown / 3600)
        let min = Math.floor((countdown % 3600) / 60)
        let sec = Math.floor(countdown % 60)

        let prefix = false

        if(prefix === true || hr > 0)
            s = s.concat(` ${hr} hr`)

        if(prefix === true || min > 0)
            s = s.concat(` ${min} min`)

        if(prefix === true || sec > 0)
            s = s.concat(` ${sec} sec`)

        return s
    }

    return (
        <div className="m-3">
        <MDBCard>
            <MDBCardBody>
            <MDBContainer>
                <MDBRow>
                <MDBCol size='1'>Site</MDBCol>
                <MDBCol size='1'>
                    <div className="fw-bold bg-light">
                    { isMain ? 'Stepup' : 'Main' }
                    </div>
                </MDBCol>

                <MDBCol size='2'>Interval</MDBCol>
                <MDBCol size='2'>
                    <MDBDropdown className="d-grid gap-2 mx-auto">
                        <MDBDropdownToggle size="sm">{interval}</MDBDropdownToggle>
                        <MDBDropdownMenu>
                            <MDBDropdownItem link onClick={changeIntervalOnChange}>1 minute</MDBDropdownItem>
                            <MDBDropdownItem link onClick={changeIntervalOnChange}>5 minutes</MDBDropdownItem>
                            <MDBDropdownItem link onClick={changeIntervalOnChange}>10 minutes</MDBDropdownItem>
                            <MDBDropdownItem link onClick={changeIntervalOnChange}>15 minutes</MDBDropdownItem>
                            <MDBDropdownItem link onClick={changeIntervalOnChange}>30 minutes</MDBDropdownItem>
                            <MDBDropdownItem divider />
                            <MDBDropdownItem link onClick={changeIntervalOnChange}>1 hour</MDBDropdownItem>
                            <MDBDropdownItem link onClick={changeIntervalOnChange}>2 hours</MDBDropdownItem>
                            <MDBDropdownItem link onClick={changeIntervalOnChange}>3 hours</MDBDropdownItem>
                            <MDBDropdownItem link onClick={changeIntervalOnChange}>6 hours</MDBDropdownItem>
                            <MDBDropdownItem link onClick={changeIntervalOnChange}>12 hours</MDBDropdownItem>
                            <MDBDropdownItem divider />
                            <MDBDropdownItem link onClick={changeIntervalOnChange}>Daily</MDBDropdownItem>
                            <MDBDropdownItem link onClick={changeIntervalOnChange}>Weekly</MDBDropdownItem>
                        </MDBDropdownMenu>
                    </MDBDropdown>
                </MDBCol>
                <MDBCol size='1'>Started</MDBCol>
                <MDBCol size='3'>
                    <div className="fw-bold bg-light">
                    {startTime == null? "Not started": startTime.toLocaleString()}
                    </div>
                </MDBCol>
                </MDBRow>

                <MDBRow>
                <MDBCol size='1'>Status</MDBCol>
                <MDBCol size='1'>
                    <div className={`fw-bold ${ isOnline ? "bg-success" : "bg-danger" } text-white`}>{ isOnline ? 'Online' : 'Offline' }</div>
                </MDBCol>
                <MDBCol size='2'>Countdown</MDBCol>
                <MDBCol size='2'>
                    <div className="fw-bold bg-light">
                    { toCountDownString( countdown ) }
                    </div>
                </MDBCol>
                <MDBCol size='1'>Ended</MDBCol>
                <MDBCol size='3'>
                    <div className="fw-bold bg-light">
                    {endTime == null? "Not ended" : endTime.toLocaleString()}
                    </div>
                </MDBCol>
                </MDBRow>
            </MDBContainer>
            </MDBCardBody>
        </MDBCard>
        </div>
    )
}
