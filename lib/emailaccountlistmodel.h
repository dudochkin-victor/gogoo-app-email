/*
 * Copyright 2011 Intel Corporation.
 *
 * This program is licensed under the terms and conditions of the
 * Apache License, version 2.0.  The full text of the Apache License is at 	
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef EMAILACCOUNTLISTMODEL_H
#define EMAILACCOUNTLISTMODEL_H

#ifdef None
#undef None
#endif
#ifdef Status
#undef Status
#endif

#include <qmailaccountlistmodel.h>
#include <QAbstractListModel>
#include <qmailaccount.h>

class EmailAccountListModel : public QMailAccountListModel
{
    Q_OBJECT

public:
    explicit EmailAccountListModel (QObject *parent = 0);
    ~EmailAccountListModel();

    enum Role {
        DisplayName = Qt::UserRole + 4,
        EmailAddress = Qt::UserRole + 5,
        MailServer = Qt::UserRole + 6,
        UnreadCount = Qt::UserRole + 7,
        MailAccountId  = Qt::UserRole + 8,
        Index = Qt::UserRole + 9,
    };

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

public slots:
    Q_INVOKABLE QVariant indexFromAccountId(QVariant id);
    Q_INVOKABLE QVariant getDisplayNameByIndex(int idx);
    Q_INVOKABLE QVariant getEmailAddressByIndex(int idx);
    Q_INVOKABLE int getRowCount();
    Q_INVOKABLE QVariant getAllEmailAddresses();
    Q_INVOKABLE QVariant getAllDisplayNames();
    Q_INVOKABLE QVariant getAccountIdByIndex(int idx);

signals:
    void accountAdded(QVariant accountId);
    void accountRemoved(QVariant accountId);
    void modelReset();

private slots:
    void onAccountsAdded(const QMailAccountIdList &);
    void onAccountsRemoved(const QMailAccountIdList &);
    void onAccountsUpdated(const QMailAccountIdList &);

private:
};

#endif
