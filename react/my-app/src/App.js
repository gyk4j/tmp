import React from 'react';
import StatusBar from './StatusBar';
import ToolBar from './ToolBar';
import TabbedPane from './TabbedPane';

import {
  MDBModal,
  MDBModalDialog,
  MDBModalContent,
  MDBModalHeader,
  MDBModalTitle,
  MDBModalBody,
  MDBModalFooter,
  MDBBtn
} from 'mdb-react-ui-kit';

export default class App extends React.Component {

  constructor(props) {
    super(props);
    this.state = {
      name: "TOC",
      showTocEndedModal: false,
      statusbarIsMain: Math.random() > 0.5,
      statusbarIsOnline: Math.random() > 0.5,
      statusbarInterval: '1 minute',
      statusbarCountdown: -1, // in seconds
      statusbarStartTime: null,
      statusbarEndTime: null,
      toolbar: null,
      tabsStatisticsTotal: 100, // kb
      tabsStatisticsTransferred: 0, // kb
      tabsStatisticsDuration: Math.floor(Math.random() * (60 * 60)),
      tabsLogsDatabase: [
        "INFO: Line 1",
        "DEBUG: Line 2",
        "TRACE: Line 3",
        "ERROR: Line 4",
        "WARN: Line 5",
        "FATAL: Line 6"
      ],
      tabsLogsEmail: [
        "INFO: Line 1",
        "DEBUG: Line 2",
        "TRACE: Line 3",
        "ERROR: Line 4",
        "WARN: Line 5",
        "FATAL: Line 6"
      ],
      tabsLogsFile: [
        "INFO: Line 1",
        "DEBUG: Line 2",
        "TRACE: Line 3",
        "ERROR: Line 4",
        "WARN: Line 5",
        "FATAL: Line 6"
      ],
      tabsLogsWeb: [
        "INFO: Line 1",
        "DEBUG: Line 2",
        "TRACE: Line 3",
        "ERROR: Line 4",
        "WARN: Line 5",
        "FATAL: Line 6"
      ],
      tabsProgressBackups: [
        {
          time: new Date(),
          database: "Backup created",
          email: "Restoration completed",
          file: "Backup failed",
          web: "Restoration failed"
        },
        {
          time: new Date(),
          database: "Backup created",
          email: "Transferring to main controller",
          file: "Transferring to file server",
          web: "Restoring backup"
        }
      ],
      tabsQuotaQuotas: [
        {
          directory: "C:\\Windows",
          total: 100,
          used: Math.floor(Math.random() * 101)
        },
        {
          directory: "C:\\Windows",
          total: 100,
          used: Math.floor(Math.random() * 101)
        },
        {
          directory: "C:\\Windows",
          total: 100,
          used: Math.floor(Math.random() * 101)
        },
        {
          directory: "C:\\Windows\\Temp",
          total: 100,
          used: Math.floor(Math.random() * 101)
        },
        {
          directory: "C:\\Users",
          total: 100,
          used: Math.floor(Math.random() * 101)
        }
      ]
    };

    this.toggleShowTocEnded = this.toggleShowTocEnded.bind(this);
    this.changeIntervalOnChange = this.changeIntervalOnChange.bind(this);
    this.startOnClick = this.startOnClick.bind(this);
    this.sendCompletedOnClick = this.sendCompletedOnClick.bind(this);
    this.sendDeltaNowOnClick = this.sendDeltaNowOnClick.bind(this);
    this.sendLastDeltaOnClick = this.sendLastDeltaOnClick.bind(this);
    this.checkQuotaOnClick = this.checkQuotaOnClick.bind(this);
    this.exportLogsOnClick = this.exportLogsOnClick.bind(this);
    this.archiveOnClick = this.archiveOnClick.bind(this);

    this.onTimer = this.onTimer.bind(this);

    this.timer = null;
    this.timerCountDown = null;
  }

  render() {
    // const [basicModal, setBasicModal] = useState(false);

    // const toggleShowTocEnded = () => setBasicModal(!basicModal);

    return (
      <div> {/* setShow={this.toggleShowTocEnded} */}
        <MDBModal show={this.state.showTocEndedModal} tabIndex='-1'>
          <MDBModalDialog>
            <MDBModalContent>
              <MDBModalHeader>
                <MDBModalTitle>TOC Ended</MDBModalTitle>
                <MDBBtn className='btn-close' color='none' onClick={this.toggleShowTocEnded}></MDBBtn>
              </MDBModalHeader>
              <MDBModalBody>TOC ended at 
                <strong className="text-danger"> { this.state.statusbarEndTime != null ? this.state.statusbarEndTime.toLocaleString() : "" }</strong>
              </MDBModalBody>
              <MDBModalFooter>
                <MDBBtn onClick={this.toggleShowTocEnded}>
                  OK
                </MDBBtn>
              </MDBModalFooter>
            </MDBModalContent>
          </MDBModalDialog>
        </MDBModal>

        <StatusBar
          isMain={this.state.statusbarIsMain} 
          isOnline={this.state.statusbarIsOnline}
          interval={this.state.statusbarInterval} 
          changeIntervalOnChange={this.changeIntervalOnChange}
          countdown={this.state.statusbarCountdown}
          startTime={this.state.statusbarStartTime}
          endTime={this.state.statusbarEndTime}
        />
        <ToolBar
          transferState={!(this.state.statusbarStartTime == null || this.state.statusbarStartTime === 'Not started')? 'STARTED': 'NOT_STARTED'}
          startOnClick={this.startOnClick}
          sendCompletedOnClick={this.sendCompletedOnClick}
          sendDeltaNowOnClick={this.sendDeltaNowOnClick}
          sendLastDeltaOnClick={this.sendLastDeltaOnClick}
          checkQuotaOnClick={this.checkQuotaOnClick}
          exportLogsOnClick={this.exportLogsOnClick}
          archiveOnClick={this.archiveOnClick} 
        />
        <TabbedPane 
          statisticsTotal={this.state.tabsStatisticsTotal}
          statisticsTransferred={this.state.tabsStatisticsTransferred}
          statisticsDuration={this.state.tabsStatisticsDuration}
          logsDatabase={this.state.tabsLogsDatabase}
          logsEmail={this.state.tabsLogsEmail}
          logsFile={this.state.tabsLogsFile}
          logsWeb={this.state.tabsLogsWeb}
          progressBackups={this.state.tabsProgressBackups}
          quotaQuotas={this.state.tabsQuotaQuotas} 
        />
      </div>
    );
  }

  toggleShowTocEnded = ( e ) => {
    let show = this.state.showTocEndedModal
    this.setState({ showTocEndedModal: !show })
  }

  changeIntervalOnChange = ( event ) => {
    //console.log(event);
    this.setState({statusbarInterval: event.target.text});
  }

  startOnClick = () => {
    console.log("startOnClick");
    // this.timer = setInterval(this.onTimer, 100);
    // this.setState({statusbarStartTime: new Date() });

    let interval = this.state.statusbarInterval.toLowerCase()
    let intervalInSec = 0
    let amount = parseInt(interval)
    
    if(interval.endsWith("minutes") || interval.endsWith("minute"))
      intervalInSec = amount * 60
    else if(interval.endsWith("hours") || interval.endsWith("hour"))
      intervalInSec = amount * 3600
    else if(interval === "daily")
      intervalInSec = 86400
    else if(interval === "weekly")
      intervalInSec = 604800
    else
      intervalInSec = 0

    console.log("interval = '" + interval + "', intervalInSec = " + intervalInSec + " seconds")

    this.resetCountDown = () => {
      let countdown = this.state.statusbarIntervalInSec
      this.setState({ statusbarCountdown: countdown })
    }
    this.resetCountDown = this.resetCountDown.bind(this)

    this.onBackup = () => {
      let now = new Date()
      console.log("Backup: " + now.toLocaleString())
      this.resetCountDown()
    }
    this.onBackup = this.onBackup.bind(this)

    // Refresh timer countdown display every second
    this.onTimerRefresh = () => {
      let countdown = this.state.statusbarCountdown

      if(isNaN(countdown) || countdown < 0){
        clearInterval(this.timerRefresh)
        this.timerRefresh = null
        console.log("Stopped timer due to non-numeric/negative countdown")
      }
      else {
        countdown-- // assumes it is triggered every second
        this.setState({ statusbarCountdown: countdown }, () => {
          if(this.state.statusbarCountdown === 0){
            this.onBackup()
          }
        })
      }
    }
    this.onTimerRefresh = this.onTimerRefresh.bind(this)

    this.onIntervalUpdated = () => {
      let intervalInSec = this.state.statusbarIntervalInSec
      if(Number.isInteger(intervalInSec)){
        console.log("onIntervalUpdated: Starting")
        this.setState({ statusbarStartTime: new Date() })
        let countdown = intervalInSec
        this.setState({ statusbarCountdown: countdown })

        if(this.timerRefresh != null)
          clearInterval(this.timerRefresh)

        this.timerRefresh = setInterval(this.onTimerRefresh, 1000)
      }
      else{
        alert("intervalInSec is NaN! " + intervalInSec)
        this.sendLastDeltaOnClick()
      }
    }
    this.onIntervalUpdated = this.onIntervalUpdated.bind(this)

    this.setState({ statusbarIntervalInSec: intervalInSec }, this.onIntervalUpdated);
  }

  sendCompletedOnClick = () => {
    console.log("sendCompletedOnClick");
  }

  sendDeltaNowOnClick = () => {
    console.log("sendDeltaNowOnClick");
  }

  sendLastDeltaOnClick = () => {

    if(this.timerRefresh != null){
      clearInterval(this.timerRefresh)
      this.timerRefresh = null
      console.log("Cleared refresh timer")
    }
    
    console.log("sendLastDeltaOnClick");
    this.setState({statusbarEndTime: new Date() }, () => {
      this.toggleShowTocEnded()
    });
  }

  checkQuotaOnClick = () => {
    console.log("checkQuotaOnClick");
  }

  exportLogsOnClick = () => {
    console.log("exportLogsOnClick");
  }

  archiveOnClick = () => {
    console.log("archiveOnClick");
  }

  onTimer = () => {
    const stopTimer = () => {
      clearInterval(this.timer);
      this.timer = null;
    }

    stopTimer.bind(this);

    let current = this.state.tabsStatisticsTransferred;
    
    if(isNaN(current)){
      stopTimer();
    }
    else {
      var progress = ++current;

      if(isNaN(progress)){
        stopTimer();
      }
      else {
        this.setState({tabsStatisticsTransferred: progress }, ()=> {
          if(this.state.tabsStatisticsTransferred === this.state.tabsStatisticsTotal){
            stopTimer();
          }
        });
      }
    }
  }
}