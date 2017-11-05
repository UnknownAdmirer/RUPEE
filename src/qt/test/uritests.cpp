#include "uritests.h"
#include "../guiutil.h"
#include "../walletmodel.h"

#include <QUrl>

void URITests::uriTests()
{
    SendCoinsRecipient rv;
    QUrl uri;
    uri.setUrl(QString("rupee:RM8VCvsN5WYdLFVpdiF5sgmoKN3syDXAtv?req-dontexist="));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("rupee:RM8VCvsN5WYdLFVpdiF5sgmoKN3syDXAtv?dontexist="));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("RM8VCvsN5WYdLFVpdiF5sgmoKN3syDXAtv"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("rupee:RM8VCvsN5WYdLFVpdiF5sgmoKN3syDXAtv?label=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("RM8VCvsN5WYdLFVpdiF5sgmoKN3syDXAtv"));
    QVERIFY(rv.label == QString("Wikipedia Example Address"));
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("rupee:RM8VCvsN5WYdLFVpdiF5sgmoKN3syDXAtv?amount=0.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("RM8VCvsN5WYdLFVpdiF5sgmoKN3syDXAtv"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100000);

    uri.setUrl(QString("rupee:RM8VCvsN5WYdLFVpdiF5sgmoKN3syDXAtv?amount=1.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("RM8VCvsN5WYdLFVpdiF5sgmoKN3syDXAtv"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100100000);

    uri.setUrl(QString("rupee:RM8VCvsN5WYdLFVpdiF5sgmoKN3syDXAtv?amount=100&label=Wikipedia Example"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("RM8VCvsN5WYdLFVpdiF5sgmoKN3syDXAtv"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Wikipedia Example"));

    uri.setUrl(QString("rupee:RM8VCvsN5WYdLFVpdiF5sgmoKN3syDXAtv?message=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("RM8VCvsN5WYdLFVpdiF5sgmoKN3syDXAtv"));
    QVERIFY(rv.label == QString());

    QVERIFY(GUIUtil::parseBitcoinURI("rupee://RM8VCvsN5WYdLFVpdiF5sgmoKN3syDXAtv?message=Wikipedia Example Address", &rv));
    QVERIFY(rv.address == QString("RM8VCvsN5WYdLFVpdiF5sgmoKN3syDXAtv"));
    QVERIFY(rv.label == QString());

    // We currently don't implement the message parameter (ok, yea, we break spec...)
    uri.setUrl(QString("rupee:RM8VCvsN5WYdLFVpdiF5sgmoKN3syDXAtv?req-message=Wikipedia Example Address"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("rupee:RM8VCvsN5WYdLFVpdiF5sgmoKN3syDXAtv?amount=1,000&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("rupee:RM8VCvsN5WYdLFVpdiF5sgmoKN3syDXAtv?amount=1,000.0&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));
}
