/*
 * Copyright 2011 Intel Corporation.
 *
 * This program is licensed under the terms and conditions of the
 * Apache License, version 2.0.  The full text of the Apache License is at 	
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef EMAILMESSAGELISTMODEL_H
#define EMAILMESSAGELISTMODEL_H

#ifdef None
#undef None
#endif
#ifdef Status
#undef Status
#endif

#include <QAbstractListModel>
#include <qmailmessage.h>
#include <qmailmessagelistmodel.h>
#include <qmailserviceaction.h>
#include <qmailaccount.h>
#include <QProcess>


class EmailMessageListModel : public QMailMessageListModel
{
    Q_OBJECT

public:
    enum Roles
    {
        MessageAttachmentCountRole = QMailMessageModelBase::MessageIdRole + 1, // returns number of attachment
        MessageAttachmentsRole,                                // returns a list of attachments
        MessageRecipientsRole,                                 // returns a list of recipients (email address)
        MessageRecipientsDisplayNameRole,                      // returns a list of recipients (displayName)
        MessageReadStatusRole,                                 // returns the read/unread status
        MessageQuotedBodyRole,                                 // returns the quoted body
        MessageHtmlBodyRole,                                   // returns the html body
        MessageUuidRole,			               // returns a unique string id
        MessageSenderDisplayNameRole,                          // returns sender's display name
        MessageSenderEmailAddressRole,                         // returns sender's email address
        MessageCcRole,                                         // returns a list of Cc (email + displayName)
        MessageBccRole,                                        // returns a list of Bcc (email + displayName)
        MessageTimeStampRole,                                  // returns timestamp in QDateTime format
        MessageSelectModeRole                                  // returns the select mode
    };


    EmailMessageListModel (QObject *parent = 0);
    ~EmailMessageListModel();
    int rowCount (const QModelIndex & parent = QModelIndex()) const;
    QVariant data (const QModelIndex & index, int role = Qt::DisplayRole) const;
    QString bodyHtmlText(QMailMessagePartContainer *container) const;
    QString bodyPlainText(const QMailMessage &) const;

signals:
    void messageDownloadCompleted();

public slots:
    Q_INVOKABLE void setFolderKey (QVariant id);
    Q_INVOKABLE void setAccountKey (QVariant id);
    Q_INVOKABLE void sortBySender (int key);
    Q_INVOKABLE void sortBySubject (int key);
    Q_INVOKABLE void sortByDate (int key);
    Q_INVOKABLE void sortByAttachment (int key);
    Q_INVOKABLE void setSearch(const QString search);

    Q_INVOKABLE QVariant indexFromMessageId(QString msgId);
    Q_INVOKABLE QVariant messageId (int index);
    Q_INVOKABLE QVariant subject (int index);
    Q_INVOKABLE QVariant mailSender (int index);
    Q_INVOKABLE QVariant timeStamp (int index);
    Q_INVOKABLE QVariant body (int index);
    Q_INVOKABLE QVariant htmlBody (int index);
    Q_INVOKABLE QVariant quotedBody (int index);
    Q_INVOKABLE QVariant attachments (int index);
    Q_INVOKABLE QVariant numberOfAttachments (int index);
    Q_INVOKABLE QVariant recipients (int index);
    Q_INVOKABLE QVariant ccList (int index);
    Q_INVOKABLE QVariant bccList (int index);
    Q_INVOKABLE QVariant toList (int index);
    Q_INVOKABLE QVariant messageRead (int index);
    Q_INVOKABLE int messagesCount ();
    Q_INVOKABLE void deSelectAllMessages();
    Q_INVOKABLE void selectMessage( int index );
    Q_INVOKABLE void deSelectMessage (int index );
    Q_INVOKABLE void deleteSelectedMessageIds();

private slots:
    void downloadActivityChanged(QMailServiceAction::Activity);

private:
    void initMailServer ();
  
    QProcess m_msgAccount;
    QMailFolderId m_currentFolderId;
    QProcess m_messageServerProcess;
    QMailAccountIdList m_mailAccountIds;
    QMailRetrievalAction *m_retrievalAction;
    QMailStorageAction *m_storageAction;
    QString m_search;
    QMailMessageKey m_key;                  // key set externally other than search
    QList<QMailMessageId> m_selectedMsgIds;
};

#endif
