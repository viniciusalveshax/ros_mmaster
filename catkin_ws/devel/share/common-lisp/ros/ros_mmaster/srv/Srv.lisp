; Auto-generated. Do not edit!


(cl:in-package ros_mmaster-srv)


;//! \htmlinclude Srv-request.msg.html

(cl:defclass <Srv-request> (roslisp-msg-protocol:ros-message)
  ((A
    :reader A
    :initarg :A
    :type cl:integer
    :initform 0)
   (B
    :reader B
    :initarg :B
    :type cl:integer
    :initform 0))
)

(cl:defclass Srv-request (<Srv-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Srv-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Srv-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros_mmaster-srv:<Srv-request> is deprecated: use ros_mmaster-srv:Srv-request instead.")))

(cl:ensure-generic-function 'A-val :lambda-list '(m))
(cl:defmethod A-val ((m <Srv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_mmaster-srv:A-val is deprecated.  Use ros_mmaster-srv:A instead.")
  (A m))

(cl:ensure-generic-function 'B-val :lambda-list '(m))
(cl:defmethod B-val ((m <Srv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_mmaster-srv:B-val is deprecated.  Use ros_mmaster-srv:B instead.")
  (B m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Srv-request>) ostream)
  "Serializes a message object of type '<Srv-request>"
  (cl:let* ((signed (cl:slot-value msg 'A)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'B)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Srv-request>) istream)
  "Deserializes a message object of type '<Srv-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'A) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'B) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Srv-request>)))
  "Returns string type for a service object of type '<Srv-request>"
  "ros_mmaster/SrvRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Srv-request)))
  "Returns string type for a service object of type 'Srv-request"
  "ros_mmaster/SrvRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Srv-request>)))
  "Returns md5sum for a message object of type '<Srv-request>"
  "713e5cf1444846805670f946f08bfc96")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Srv-request)))
  "Returns md5sum for a message object of type 'Srv-request"
  "713e5cf1444846805670f946f08bfc96")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Srv-request>)))
  "Returns full string definition for message of type '<Srv-request>"
  (cl:format cl:nil "int64 A~%int64 B~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Srv-request)))
  "Returns full string definition for message of type 'Srv-request"
  (cl:format cl:nil "int64 A~%int64 B~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Srv-request>))
  (cl:+ 0
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Srv-request>))
  "Converts a ROS message object to a list"
  (cl:list 'Srv-request
    (cl:cons ':A (A msg))
    (cl:cons ':B (B msg))
))
;//! \htmlinclude Srv-response.msg.html

(cl:defclass <Srv-response> (roslisp-msg-protocol:ros-message)
  ((Sum
    :reader Sum
    :initarg :Sum
    :type cl:integer
    :initform 0))
)

(cl:defclass Srv-response (<Srv-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Srv-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Srv-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros_mmaster-srv:<Srv-response> is deprecated: use ros_mmaster-srv:Srv-response instead.")))

(cl:ensure-generic-function 'Sum-val :lambda-list '(m))
(cl:defmethod Sum-val ((m <Srv-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_mmaster-srv:Sum-val is deprecated.  Use ros_mmaster-srv:Sum instead.")
  (Sum m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Srv-response>) ostream)
  "Serializes a message object of type '<Srv-response>"
  (cl:let* ((signed (cl:slot-value msg 'Sum)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Srv-response>) istream)
  "Deserializes a message object of type '<Srv-response>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'Sum) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Srv-response>)))
  "Returns string type for a service object of type '<Srv-response>"
  "ros_mmaster/SrvResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Srv-response)))
  "Returns string type for a service object of type 'Srv-response"
  "ros_mmaster/SrvResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Srv-response>)))
  "Returns md5sum for a message object of type '<Srv-response>"
  "713e5cf1444846805670f946f08bfc96")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Srv-response)))
  "Returns md5sum for a message object of type 'Srv-response"
  "713e5cf1444846805670f946f08bfc96")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Srv-response>)))
  "Returns full string definition for message of type '<Srv-response>"
  (cl:format cl:nil "int64 Sum~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Srv-response)))
  "Returns full string definition for message of type 'Srv-response"
  (cl:format cl:nil "int64 Sum~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Srv-response>))
  (cl:+ 0
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Srv-response>))
  "Converts a ROS message object to a list"
  (cl:list 'Srv-response
    (cl:cons ':Sum (Sum msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'Srv)))
  'Srv-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'Srv)))
  'Srv-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Srv)))
  "Returns string type for a service object of type '<Srv>"
  "ros_mmaster/Srv")