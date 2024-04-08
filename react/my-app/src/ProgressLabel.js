import {
    MDBBadge,
} from 'mdb-react-ui-kit';

export default function ProgressLabel({
    progress
}) {

    let color = null

    if(progress.endsWith('failed'))
        color = 'danger'
    else if(progress.endsWith("completed"))
        color = 'success'
    else if(progress.startsWith("Transferring"))
        color = 'warning'
    else
        color = 'info'

    return (
        <MDBBadge color={ color } pill>
        { progress }
        </MDBBadge>
    )
}