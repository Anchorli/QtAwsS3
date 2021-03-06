#include "s3objectreply.h"
#include "s3objectreply_p.h"

#include <QNetworkReply>

S3ObjectReply::S3ObjectReply(QNetworkReply *reply)
    : QObject(nullptr)
    , d_ptr(new S3ObjectReplyPrivate(this))
{
    d_ptr->m_reply = reply;
    connect(reply, &QNetworkReply::finished, this, &S3ObjectReply::finished);
    connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &S3ObjectReply::error);
    connect(reply, &QNetworkReply::sslErrors, this, &S3ObjectReply::sslErrors);
    connect(reply, &QNetworkReply::sslErrors, this, &S3ObjectReply::handleSSLErrors);
    connect(reply, &QNetworkReply::uploadProgress, this, &S3ObjectReply::uploadProgress);
    connect(reply, &QNetworkReply::downloadProgress, this, &S3ObjectReply::downloadProgress);
}

bool S3ObjectReply::isFinished() const
{
    Q_D(const S3ObjectReply);
    return d->m_reply->isFinished();
}

bool S3ObjectReply::isRunning() const
{
    Q_D(const S3ObjectReply);
    return d->m_reply->isRunning();
}

QByteArray S3ObjectReply::readAll()
{
    Q_D(S3ObjectReply);
    return d->m_reply->readAll();
}

void S3ObjectReply::handleSSLErrors(const QList<QSslError> aErrors)
{
    QNetworkReply * reply = qobject_cast<QNetworkReply *>(sender());
    reply->ignoreSslErrors();
}


