import {
    MDBContainer, 
} from 'mdb-react-ui-kit';

export default function TabLogs({
    database,
    email,
    file,
    web
  }) {
    const format = (line) => {
      if(line.startsWith("FATAL"))
        return "text-danger"
      else if(line.startsWith("ERROR"))
        return "text-danger"
      else if(line.startsWith("WARN"))
        return "text-warning"
      else if(line.startsWith("INFO"))
        return "text-info"
      else if(line.startsWith("DEBUG"))
        return "text-dark"
      else if(line.startsWith("TRACE"))
        return "text-muted"
      else
        return ""
    }
  
    return (
      <>
        <MDBContainer fluid>
          <strong>Database</strong>
        </MDBContainer>
  
        <MDBContainer fluid>
          <div className="overflow-scroll p-3 bg-light" style={{ maxHeight: "100px" }}>          
            {
              database.map((line, index) => 
              (<div key={index} className={ format(line) }>{line}</div>))
            }
          </div>
        </MDBContainer>
  
        <MDBContainer fluid>
          <strong>Email</strong>
        </MDBContainer>
  
        <MDBContainer fluid>
          <div className="overflow-scroll p-3 bg-light" style={{ maxHeight: "100px" }}>          
            {
              email.map((line, index) => 
              (<div key={index} className={ format(line) }>{line}</div>))
            }
          </div>
        </MDBContainer>
          
        <MDBContainer fluid>
          <strong>File</strong>
        </MDBContainer>
  
        <MDBContainer fluid>
          <div className="overflow-scroll p-3 bg-light" style={{ maxHeight: "100px" }}>          
            {
              file.map((line, index) => 
              (<div key={index} className={ format(line) }>{line}</div>))
            }
          </div>
        </MDBContainer>
  
        <MDBContainer fluid>
          <strong>Web</strong>
        </MDBContainer>
  
        <MDBContainer fluid>
          <div className="overflow-scroll p-3 bg-light" style={{ maxHeight: "100px" }}>          
            {
              web.map((line, index) => 
              (<div key={index} className={ format(line) }>{line}</div>))
            }
          </div>
        </MDBContainer>
      </>
    )
  }