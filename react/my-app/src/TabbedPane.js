import { useState } from 'react';
import TabStatistics from './TabStatistics';
import TabLogs from './TabLogs';
import TabProgress from './TabProgress.js';
import TabQuota from './TabQuota';

import {
    MDBCard,
    MDBCardBody,
    //MDBCardTitle,
    //MDBCardText,
    MDBTabs,
    MDBTabsItem,
    MDBTabsLink,
    MDBTabsContent,
    MDBTabsPane,
} from 'mdb-react-ui-kit';

export default function TabbedPane({
  statisticsTotal,
  statisticsTransferred,
  statisticsDuration,
  logsDatabase,
  logsEmail,
  logsFile,
  logsWeb,
  progressBackups,
  quotaQuotas,
}) {
  const [basicActive, setBasicActive] = useState('tabStatistics');

  const handleBasicClick = (value) => {
    if (value === basicActive) {
      return;
    }

    setBasicActive(value);
  };

  return (
    <div className="m-3">
      <MDBCard>
      <MDBCardBody>
      <MDBTabs className='mb-3'>
        <MDBTabsItem>
          <MDBTabsLink onClick={() => handleBasicClick('tabStatistics')} active={basicActive === 'tabStatistics'}>
            Statistics
          </MDBTabsLink>
        </MDBTabsItem>
        <MDBTabsItem>
          <MDBTabsLink onClick={() => handleBasicClick('tabLogs')} active={basicActive === 'tabLogs'}>
            Logs
          </MDBTabsLink>
        </MDBTabsItem>
        <MDBTabsItem>
          <MDBTabsLink onClick={() => handleBasicClick('tabProgress')} active={basicActive === 'tabProgress'}>
            Progress
          </MDBTabsLink>
        </MDBTabsItem>
        <MDBTabsItem>
          <MDBTabsLink onClick={() => handleBasicClick('tabQuota')} active={basicActive === 'tabQuota'}>
            Quota
          </MDBTabsLink>
        </MDBTabsItem>
      </MDBTabs>

      <MDBTabsContent>
        <MDBTabsPane show={basicActive === 'tabStatistics'}>
          <TabStatistics 
            total={statisticsTotal}
            transferred={statisticsTransferred}
            duration={statisticsDuration} 
          />
        </MDBTabsPane>
        
        <MDBTabsPane show={basicActive === 'tabLogs'}>
          <TabLogs 
            database={logsDatabase}
            email={logsEmail}
            file={logsFile}
            web={logsWeb} 
          />
        </MDBTabsPane>

        <MDBTabsPane show={basicActive === 'tabProgress'}>
          <TabProgress
            backups={progressBackups}
          />
        </MDBTabsPane>
        
        <MDBTabsPane show={basicActive === 'tabQuota'}>
          <TabQuota 
            quotas={quotaQuotas} 
          />
        </MDBTabsPane>
      </MDBTabsContent>

      </MDBCardBody>
    </MDBCard>
    </div>
  )
}