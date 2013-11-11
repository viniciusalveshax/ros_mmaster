
(cl:in-package :asdf)

(defsystem "ros_mmaster-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Srv" :depends-on ("_package_Srv"))
    (:file "_package_Srv" :depends-on ("_package"))
  ))